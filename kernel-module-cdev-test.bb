SUMMARY = "Sample character driver"
LICENSE = "GPL-2.0"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/GPL-2.0;md5=801f80980d171dd6425610833a22dbe6"

SRC_URI = " file://cdev_test.c \
	file://Makefile \
"

FILESEXTRAPATHS_prepend := "${THISDIR}/cdev:"
S = "${WORKDIR}"

do_unpack_extra() {
	    mkdir -p ${WORKDIR}/src
	    cp -rf ${WORKDIR}/cdev_test.c  ${S}/src/
	    cp -rf ${WORKDIR}/Makefile ${S}/src/
}

addtask unpack_extra after do_unpack before do_patch

inherit module

COMPATIBLE_MACHINE = "(imx)"
