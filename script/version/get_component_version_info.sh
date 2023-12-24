#!/bin/bash

#-------------------------------------------------------------------------------

# get parameters

TARGET_DIR_PARAM="$1"
COMPONENT_NAME=$( basename $PWD )

#-------------------------------------------------------------------------------

# declare output file name and etc

VERSION_INFO_FILE_NAME="version_info"
VERSION_INFO_FILE_EXT="txt"
GIT_HAS_UNTRACKED=" (with some untracked)"
ERROR_NO_GIT_REPOSITORY="<git repository is missing>"
ERROR_NO_VERSION_INFO_GENERATED="<skipped the version info file generation>"
ERROR_NO_TARGET_DIR_EXISTS="<no target directory exists>"

#-------------------------------------------------------------------------------

# get current or target folder

GIT_BRANCH_NAME="<git branch is unknown>"
GIT_HEAD_COMMIT="<git HEAD commit is unknown>"
GIT_IF_DIRTY_COMMIT="<git dirty status is unknown>"

#-------------------------------------------------------------------------------

function get_output_file_name()
{
    echo "${VERSION_INFO_FILE_NAME}.${VERSION_INFO_FILE_EXT}"
}

#-------------------------------------------------------------------------------

function get_git_status()
{
    echo "$( git status || echo "${ERROR_NO_GIT_REPOSITORY}" )"
}

#-------------------------------------------------------------------------------

function get_git_branch_name()
{
    echo "$( git branch  --show-current )"
}

#-------------------------------------------------------------------------------

function get_git_head_commit()
{
    echo "$( git rev-parse HEAD )"
}

#-------------------------------------------------------------------------------

function get_is_git_dirty_commit()
{
    echo "$( git diff-index --quiet HEAD -- || echo "${GIT_HAS_UNTRACKED}" )"
}

#-------------------------------------------------------------------------------

function collect_version_info()
{
    # get the target component name

    COMPONENT_NAME=$( basename $PWD )

    # get version information

    GIT_BRANCH_NAME=$( get_git_branch_name )
    GIT_HEAD_COMMIT=$( get_git_head_commit )
    GIT_IF_DIRTY_COMMIT=$( get_is_git_dirty_commit )
}

#-------------------------------------------------------------------------------

function generate_version_info()
{

cat << EOF_CAT > "$( get_output_file_name )"
Component name: ${COMPONENT_NAME}
Revision name: ${GIT_BRANCH_NAME}
Git commit: ${GIT_HEAD_COMMIT}${GIT_IF_DIRTY_COMMIT}
EOF_CAT

}

#-------------------------------------------------------------------------------

function process_version_info()
{
    # check if there is a git repo

    GIT_STATUS=$( get_git_status )

    if [ "${GIT_STATUS}" != "${ERROR_NO_GIT_REPOSITORY}" ]
    then

        # collect the output file contents

        collect_version_info

        # generate and write down the output file contents

        generate_version_info
    else
        echo "${ERROR_NO_VERSION_INFO_GENERATED}"
    fi
}

#-------------------------------------------------------------------------------

function main()
{
    if [ -n "${TARGET_DIR_PARAM}" ]
    then
        # open new subshell

        (
            # go to the specified component's folder

            cd $TARGET_DIR_PARAM \
            && process_version_info \
            || echo "${ERROR_NO_TARGET_DIR_EXISTS}"


        ) # close the subshell
    else
        # process the component as regular

        process_version_info
    fi
}

#-------------------------------------------------------------------------------
#
#   MAIN
#
#-------------------------------------------------------------------------------

main

