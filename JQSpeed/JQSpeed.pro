TEMPLATE = subdirs

win32-msvc {
    SUBDIRS += JQSpeedClient
    SUBDIRS += JQSpeedServer
}

wasm {
    SUBDIRS += JQSpeedClient
    SUBDIRS -= JQSpeedServer
}
