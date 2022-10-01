#!/bin/bash
# Generate .clang-format file based on google style guide 
# clang-format -style=google -dump-config > .clang-format

# view format output for the wclip.cpp file
# clang-format --style=file wclip.cpp

# format wclip.cpp file
# clang-format --style=file -i wclip.cpp

# format all the .cpp file 
# clang-format --style=file -i *.cpp

#  format all .h, .c, .hpp, .cpp, .cu files together
# find . -regex '.*\.\(cpp\|hpp\|cu\|c\|h\)' -exec clang-format -style=file -i {} \;
#

me=`basename "$0"`

while getopts 'hgca:v:i:' OPTION; do
  case "$OPTION" in
    h)
      echo "Script usage: $me [-g] [-v filename] [-i filename] [-c] [-a] [-h]"
      echo ""
      echo "Flags:"
      echo "-g                    Generate .clang-format file based on google style guide"
      echo "-v <filename>         View formatted output for the given file not save the file"
      echo "-i <filename>         Format the given file and save"
      echo "-c                    Format all the .cpp files in the directory"
      echo "-a                    Format all the .cpp, .hpp, .cu, .c, .h files in the directory"
      echo "-h                    Show help"
      ;;
    g)
      echo "Generate .clang-format file based on google style guide"
      clang-format -style=google -dump-config > .clang-format
      ;;
    c)
      echo "Format all the .cpp files"
      clang-format --style=file -i *.cpp
      ;;
    a)
      echo "Format all .h, .c, .hpp, .cpp, .cu files together"
      find . -regex '.*\.\(cpp\|hpp\|cu\|c\|h\)' -exec clang-format -style=file -i {} \;
      ;;
    v)
      vvalue="$OPTARG"
      echo "//View formated output for $vvalue"
      clang-format --style=file $vvalue | batcat -l c++
      ;;
    i)
      ivalue="$OPTARG"
      echo "Format the file: $ivalue"
      clang-format --style=file -i $ivalue
      ;;
    ?)
      echo "Script usage: $me [-g] [-v filename] [-i filename] [-c] [-a] [-h]"
      exit 1
      ;;
  esac
done
shift "$(($OPTIND -1))"
