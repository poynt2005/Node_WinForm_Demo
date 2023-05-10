import os
import subprocess
import shutil
import urllib.request


msvc2019_tool_path = os.path.join(os.environ['ProgramFiles(x86)'],
                                  'Microsoft Visual Studio', '2019', 'Professional', 'Common7', 'Tools')

os.environ['PATH'] += ';%s' % msvc2019_tool_path


def run_msbuild(directory):
    sb = subprocess.Popen(
        ['cmd.exe'],
        cwd=directory,
        shell=True,
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE
    )

    sb.stdin.write('VsDevCmd\r\n'.encode('utf-8'))
    sb.stdin.flush()
    sb.stdin.write(
        'MSBuild /property:Configuration=Release\r\n'.encode('utf-8'))
    sb.stdin.flush()
    sb.communicate()


print('Build csdll')
run_msbuild(os.path.join(os.getcwd(), 'csdll', 'CallWinForm'))

print('build winform')
run_msbuild(os.path.join(os.getcwd(), 'winform', 'windormDll'))

shutil.copy(
    os.path.join(os.getcwd(), 'csdll', 'CallWinForm',
                 'x64', 'Release', 'CallWinForm.dll'),
    os.path.join(os.getcwd(), 'Node', 'CallWinForm.dll')
)

shutil.copy(
    os.path.join(os.getcwd(), 'winform', 'windormDll',
                 'windormDll', 'bin', 'Release', 'winformDll.dll'),
    os.path.join(os.getcwd(), 'Node', 'winformDll.dll')
)

print('Install node module')
sb = subprocess.Popen(
    ['npm', 'i', '--ignore-scripts'],
    cwd=os.path.join(os.getcwd(), 'Node'),
    shell=True,
)
sb.wait()

print('Build node native binding')
sb = subprocess.Popen(
    ['npm', 'run', 'build-native', '&&', 'npm', 'run', 'build-executable'],
    cwd=os.path.join(os.getcwd(), 'Node'),
    shell=True,
)
sb.wait()
