SUMMARY = "Simple Hello World application"
DESCRIPTION = "A simple C program that prints Hello Yocto"
LICENSE = "MIT"

SRC_URI = "file://helloworld.c file://LICENSE"
LIC_FILES_CHKSUM = "file://LICENSE;md5=d33fac0dc3b338ef9b140ec6dc7edf15"

S = "${WORKDIR}"

do_compile() {
    ${CC} ${CFLAGS} ${LDFLAGS} helloworld.c -o helloworld
}

do_install() {
    install -d ${D}${bindir}
    install -m 0755 helloworld ${D}${bindir}
}
