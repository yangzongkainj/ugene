# include (test_runner.pri)
include(../../ugene_globals.pri)

QT += testlib

useWebKit() {
    QT += webkitwidgets
} else {
    QT += webenginewidgets
}

PLUGIN_ID=test_runner
PLUGIN_NAME=Test runner
PLUGIN_VENDOR=Unipro
PLUGIN_MODE=ui

include( ../../ugene_plugin_common.pri )
