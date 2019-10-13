import argparse
import os
from subprocess import check_output
from distutils.dir_util import copy_tree

parser = argparse.ArgumentParser(description='Prepare project for building')
parser.add_argument('jsDir')
parser.add_argument('targetDir')

args = parser.parse_args()

jsDir = os.path.join(args.jsDir,'build','js')
jsTargetDir = os.path.join(args.targetDir,'js')

print("Copying from: "+jsDir)
print("Copying to: "+jsTargetDir)

copy_tree(jsDir,jsTargetDir)