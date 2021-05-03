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
BUILDDIR=`pwd`/build-dist-linux


################### Extract the version info ###################
# source ./gitversion.sh
GIT_VERSION=`git rev-parse --short HEAD`
VERSION=${GIT_VERSION}

################## Build DKV2 ##########################
mkdir -p ${BUILDDIR}
pushd ${BUILDDIR}

${QMAKE} ${SOURCEDIR}/DKV2.pro \
    -spec linux-g++ \
    CONFIG+=qtquickcompiler

#${MAKE} clean
${MAKE} -j6

################## Package using linuxdeployqt #################
mkdir -p app
pushd app
cp ${SOURCEDIR}/res/logo256.png dkv2.png
cp ${SOURCEDIR}/res/DKV2.desktop ./
mv ${BUILDDIR}/DKV2 ./
popd

unset LD_LIBRARY_PATH # Remove too old Qt from the search path
# LINUXDEPLOYQT_OPTS=-unsupported-allow-new-glibc
PATH=${QTDIR}/bin:${PATH} ${LINUXDEPLOYQT} app/DKV2 -bundle-non-qt-libs ${LINUXDEPLOYQT_OPTS}
PATH=${QTDIR}/bin:${PATH} ${LINUXDEPLOYQT} app/DKV2 -appimage ${LINUXDEPLOYQT_OPTS}

ARTIFCACT_FILENAME="DKV2-${VERSION}-x86_64.tar.gz"
tar -czf ${ARTIFCACT_FILENAME} DKV2-${GIT_VERSION}-x86_64.AppImage
echo "Created ${BUILDDIR}/${ARTIFCACT_FILENAME}"
