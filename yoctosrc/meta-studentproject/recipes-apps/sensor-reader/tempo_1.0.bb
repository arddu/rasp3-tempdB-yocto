SUMMARY = "DS18B20 sensor reader"
DESCRIPTION = "Reads DS18B20 sensor values and prints them to console"
LICENSE = "MIT"

SRC_URI = "file://tempo.c file://LICENSE"
LIC_FILES_CHKSUM = "file://LICENSE;md5=d33fac0dc3b338ef9b140ec6dc7edf15"

S = "${WORKDIR}"

do_compile() {
    ${CC} ${CFLAGS} ${LDFLAGS} tempo.c -o tempo
}

do_install() {
    install -d ${D}${bindir}
    install -m 0755 tempo ${D}${bindir}
}
