#!/usr/bin/env bash

verbose=0
usage() {                                 # Function: Print a help message.
  echo "Usage: $0 [ -p PLATFORM_FOLDER ] [ -t VERSION_TAG ] [ -n PACKAGE_NAME ]" 1>&2 
}
exit_with_error() {
    usage
    exit 1
}

while getopts "h?vp:t:n:" opt; do
  case "$opt" in
    h|\?)
      usage
      exit 0
      ;;
    v) 
      verbose=1
      ;;
    p)  
      PLATFORM_FOLDER=$OPTARG
      ;;
    t)
      PACKAGE_VERSION=$OPTARG
      ;;
    n)
      PACKAGE_NAME=$OPTARG
      ;;
  esac
done

: ${PLATFORM_FOLDER:?"Missing option -p (platform folder) $(exit_with_error)"}
: ${PACKAGE_VERSION:?"Missing option -t (version tag) $(exit_with_error)"}
: ${PACKAGE_NAME:?"Missing option -n (package name) $(exit_with_error)"}

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
README_PATH=$SCRIPT_DIR/readme.txt

source $SCRIPT_DIR/$PLATFORM_FOLDER/definitions.sh
source $SCRIPT_DIR/$PLATFORM_FOLDER/file_content_generator.sh

# load template file and prepare output
originalTemplateFile=$SCRIPT_DIR/$PLATFORM_FOLDER/$templateFileName
outputFile="$(pwd)/$outputFileName"
templateFileContent=$(cat ${originalTemplateFile})

###### generate package and files sections
packageSection=""
fileSection=""

# binaries
binaryDir=${SCRIPT_DIR}/../build/bin
binaryFolders=$(find ${binaryDir} -type d -depth 1)
for subDir in $binaryFolders; do
    localPackageSection="$(generate_package_section $(basename $subDir))"
    packageSection+=$localPackageSection

    localFileSection="$(generate_file_section $(basename $subDir) ${PACKAGE_VERSION} $subDir 1)"
    fileSection+=$localFileSection
done

# templates
templateDir=${SCRIPT_DIR}/Templates
templateFolders=$(find ${templateDir} -type d -depth 1)
for subDir in $templateFolders; do
    localPackageSection="$(generate_package_section $(basename $subDir))"
    packageSection+=$localPackageSection

    localFileSection="$(generate_file_section $(basename $subDir) ${PACKAGE_VERSION} $subDir 0)"
    fileSection+=$localFileSection
done

# finally replace template file content and write file
templateFileContent=${templateFileContent//$readmePathMark/$README_PATH}
templateFileContent=${templateFileContent//$packageNameMark/$PACKAGE_NAME}
templateFileContent=${templateFileContent//$installerSectionMark/$packageSection}
templateFileContent=${templateFileContent//$packageSectionMark/$fileSection}
templateFileContent=${templateFileContent//$packageVersionMark/$packageVersion}

write_file "$templateFileContent" "$outputFile"
echo "----------- build installer done ----------"
exit 0
