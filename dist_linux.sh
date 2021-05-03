#!/bin/bash

# Stop at any error
set -e

# Location of the QT tools
if [ -z ${QTDIR+x} ]; then
	QTDIR=${Qt5_Dir}
fi

# Location of the QT tools
if [ -z ${QTDIR+x} ]; then
	echo "QTDIR not defined- please set it to the location containing the Qt version to build against. For example:"
	echo "  export QTDIR=~/Qt/5.15.0/gcc_64"
	exit 1
fi

QMAKE=${QTDIR}/bin/qmake
MAKE=make
LINUXDEPLOYQT=`pwd`/linuxdeployqt-continuous-x86_64.AppImage
# LINUXDEPLOYQT="linuxdeployqt"

# Location of the source tree
SOURCEDIR=`pwd`/DKV2

# Location to build DKV2
BUILDDIR='build-dist-linux'


################### Extract the version info ###################
# source ./gitversion.sh
VERSION='0.0.1'

################## Build DKV2 ##########################
mkdir -p ${BUILDDIR}
pushd ${BUILDDIR}

${QMAKE} ${SOURCEDIR}/DKV2.pro \
    -spec linux-g++ \
    CONFIG+=qtquickcompiler

#${MAKE} clean
${MAKE} -j6

popd

################## Package using linuxdeployqt #################
pushd ${BUILDDIR}
# pushd app
# icns2png ${SOURCEDIR}/app/images/patternpaint.icns -x
# cp patternpaint_256x256x32.png patternpaint.png
# cp ${SOURCEDIR}/app/patternpaint.desktop ./
# popd


# TODO: this should be done automagically though the qt build tools?
# mkdir -p app/lib
# cp libblinky/libblinky.so.1 app/lib

unset LD_LIBRARY_PATH # Remove too old Qt from the search path; TODO: Move inside the linuxdeployqt AppImage

#LINUXDEPLOYQT_OPTS=-unsupported-allow-new-glibc
PATH=${QTDIR}/bin:${PATH} ${LINUXDEPLOYQT} DKV2 -bundle-non-qt-libs ${LINUXDEPLOYQT_OPTS}
PATH=${QTDIR}/bin:${PATH} ${LINUXDEPLOYQT} DKV2 -appimage ${LINUXDEPLOYQT_OPTS}

tar -czf DKV2-${VERSION}-x86_64.tar.gz DKV2-${VERSION}-x86_64.AppImage

popd
