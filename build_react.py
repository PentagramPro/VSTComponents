import argparse
import os
from subprocess import check_output

parser = argparse.ArgumentParser(description='Prepare project for building')
parser.add_argument('jsDir')

args = parser.parse_args()

jsDir = args.jsDir.replace('\\','/')

print("js path: "+jsDir)

check_output('npm run build', cwd=jsDir, shell=True)

