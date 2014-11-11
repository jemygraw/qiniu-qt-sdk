######################################################################
# Automatically generated by qmake (3.0) Wed Oct 15 17:49:25 2014
######################################################################

QT       += core network gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
TARGET = "Qiniu Qt SDK"
INCLUDEPATH += . ui qiniu test

# Input
HEADERS += \
        qiniu/auth/QNMac.h \
        qiniu/conf/QNConf.h \
        qiniu/err/QNError.h \
        qiniu/fop/QNFop.h \
        qiniu/io/QNIOHelper.h \
        qiniu/resumable_io/QNResumableIO.h \
        qiniu/rs/QNRS.h \
        qiniu/rs/QNPutPolicy.h \
        qiniu/rs/QNPutExtra.h \
        qiniu/rs/QNPutRet.h \
        qiniu/rsf/QNRSF.h \
        qiniu/utils/QNETag.h \
        qiniu/utils/QNUtils.h \
        qiniu/utils/QNUrl.h \
        test/Base64Test.h \
        test/MacDigestTest.h \
        test/QNUrlTest.h \
        test/QNETagTest.h \
        test/QNPutPolicyTest.h \
        ui/QNMainWindow.h \
    ui/QNSimpleUploadDataWidget.h \
    ui/QNCreateSaveAsTokenWidget.h \
    ui/QNUrlBase64Widget.h



SOURCES += main.cpp \
        qiniu/auth/QNMac.cpp \
        qiniu/conf/QNConf.cpp \
        qiniu/err/QNError.cpp \
        qiniu/fop/QNFop.cpp \
        qiniu/io/QNIOHelper.cpp \
        qiniu/resumable_io/QNResumableIO.cpp \
        qiniu/rs/QNRS.cpp \
        qiniu/rs/QNPutPolicy.cpp \
        qiniu/rs/QNPutExtra.cpp \
        qiniu/rs/QNPutRet.cpp \
        qiniu/rsf/QNRSF.cpp \
        qiniu/utils/QNUtils.cpp \
        qiniu/utils/QNEtag.cpp \
        qiniu/utils/QNUrl.cpp \
        test/Base64Test.cpp \
        test/MacDigestTest.cpp \
        test/QNUrlTest.cpp \
        test/QNETagTest.cpp \
        test/QNPutPolicyTest.cpp \
        ui/QNMainWindow.cpp \
    ui/QNSimpleUploadDataWidget.cpp \
    ui/QNCreateSaveAsTokenWidget.cpp \
    ui/QNUrlBase64Widget.cpp




