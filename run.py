import subprocess
import sys
import re


def run_cpp(config_file=''):
    subprocess.call('cmake -S . -B build -G "Unix Makefiles"')
    subprocess.call('cmake --build build') 
    # curr_time = str(subprocess.check_output("./build/CountWords" + config_file))[2:-1].strip("\\n\\r")
    curr_time = subprocess.check_output("./build/CountWords" + config_file).decode("utf-8")

    return curr_time

if __name__ == '__main__':

    num_attr = len(sys.argv) - 1
    if num_attr != 0 and num_attr != 1:
        raise Exception("Wrong number of arguments!")

    if num_attr == 1:
        total = run_cpp(config_file=' ' + sys.argv[1])
    else:
        total = run_cpp()
    print("Total time(seconds) :", total)
