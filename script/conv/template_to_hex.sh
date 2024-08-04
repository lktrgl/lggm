#!/bin/env bash

#-----------------------------------------------------------------------------

WORK_AREA="$1"
SRC_FILE_RELATIVE_NAME="$2"
DEST_FILE_RELATIVE_NAME="$3"

#-----------------------------------------------------------------------------

XXD_UTIL=xxd

SRC_FILE_PATHNAME="${WORK_AREA}/${SRC_FILE_RELATIVE_NAME}"
DEST_FILE_PATHNAME="${WORK_AREA}/${DEST_FILE_RELATIVE_NAME}"

CMD_SED1="sed 's/unsigned char/#ifdef __cplusplus\nconstexpr\n#else\nstatic\n#endif\nconst uint8_t/g'"
CMD_SED2="sed 's/unsigned int/#ifdef __cplusplus\nconstexpr\n#else\nstatic\n#endif\nconst size_t/g'"

#-----------------------------------------------------------------------------

function usage()
{
    echo
    echo "$0 </absolute-or-relative/path/to/work_folder> <relative/path/to/template-source-file-name> <relative/path/to/destination-file-name>"
}

#-----------------------------------------------------------------------------

function print_fatal_error()
{
    local error_msg="$1"
    echo "Error: $1."
    exit 1
}

#-----------------------------------------------------------------------------

function check_input_params()
{
    if [ -z "$( which ${XXD_UTIL} )" ] ; then
        usage
        print_fatal_error "there is no prerequisite '${XXD_UTIL}' utility detected"
    fi

    if [ -z "${WORK_AREA}" ] ; then
        usage
        print_fatal_error "no work area has been specified"
    fi

    if [ -z "${SRC_FILE_RELATIVE_NAME}" ] ; then
        usage
        print_fatal_error "no source file has been specified"
    fi

    if [ -z "${DEST_FILE_RELATIVE_NAME}" ] ; then
        usage
        print_fatal_error "no dest file has been specified"
    fi


    if [ ! -d "${WORK_AREA}" ] ; then
        usage
        print_fatal_error "cannot find work area (got '${WORK_AREA}')"
    fi

    if [ ! -f "${SRC_FILE_PATHNAME}" ] ; then
        usage
        print_fatal_error "cannot find the source file (got '${SRC_FILE_RELATIVE_NAME}')"
    fi
}

#-----------------------------------------------------------------------------

function touch_output_file()
{
    local out_file_name="$1"

    [ -f "${out_file_name}" ] && rm -f "${out_file_name}"
    touch "${out_file_name}"
}


#-----------------------------------------------------------------------------

function get_file_contents_to_comment_block()
{
	local in_file_pathname="$1"
	local buffer_str=$( cat ${in_file_pathname} )

	local token1_to_remove="\\/\\*"
	local token2_to_remove="\\*\\/"

	buffer_str="${buffer_str//${token1_to_remove}/}"
	buffer_str="${buffer_str//${token2_to_remove}/}"

	echo -e "/*\n\nOrigin text data:\n====================\n\n${buffer_str}\n*/"
}

#-----------------------------------------------------------------------------

function prepare_output_file_header()
{
    local out_file_name="$1"

    cat <<EOF_OUTPUT_FILE_HEADER >> "${out_file_name}"
#pragma once

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
namespace gen::code_template
{
#endif

EOF_OUTPUT_FILE_HEADER
}

#-----------------------------------------------------------------------------

function prepare_output_file_contents()
{
	local in_file_pathname="$1"
	local out_file_pathname="$2"
    
	(
		local in_file_dir=$( dirname ${in_file_pathname} )
		local in_file_name=$( basename ${in_file_pathname} )

		cd ${in_file_dir} \
	    		&& eval "${XXD_UTIL} -i "${in_file_name}" | ${CMD_SED1} | ${CMD_SED2}" >> "${out_file_pathname}"
	)
}

#-----------------------------------------------------------------------------

function prepare_output_file_footer()
{
	local in_file_pathname="$1"
    local out_file_pathname="$2"

    cat <<EOF_OUTPUT_FILE_FOOTER >> "${out_file_pathname}"

#ifdef __cplusplus
} // namespace gen::code_template
#endif

$( get_file_contents_to_comment_block "${in_file_pathname}" )

EOF_OUTPUT_FILE_FOOTER
}

#-----------------------------------------------------------------------------

function main()
{
    check_input_params

    touch_output_file "${DEST_FILE_PATHNAME}"
    prepare_output_file_header "${DEST_FILE_PATHNAME}"
    prepare_output_file_contents "${SRC_FILE_PATHNAME}" "${DEST_FILE_PATHNAME}"
    prepare_output_file_footer "${SRC_FILE_PATHNAME}" "${DEST_FILE_PATHNAME}"
}

#-----------------------------------------------------------------------------
#
#    MAIN
#
#-----------------------------------------------------------------------------

main
