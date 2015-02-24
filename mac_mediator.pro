# ============================================================================
#           Project title       :
#           Project description :
#           Project version     :
#           Author              :   M. Ivanchenko
#           Date create         :   19-09-2013
#           Date update         :   19-09-2013
#           Comment             :
# ============================================================================
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = app_mac_mediator
DESTDIR = ./bin

TEMPLATE = app


SOURCES += \
    app/main.cpp \
    gui/main_window.cpp \
    logic/business_logic.cpp \
    gui/widget_search_card.cpp \
    gui/widget_central.cpp \
    gui/widget_card_view.cpp \
    gui/listview_request.cpp \
    gui/delegate_line_edit.cpp \
    gui/combobox_mr.cpp \
    gui/combobox_mediator.cpp \
    gui/combobox_ad.cpp \
    dbmodule/data_adapter_request.cpp \
    qt_sqlite/qt_sqlite_dbvalue.cpp \
    qt_sqlite/qt_sqlite_connection.cpp \
    qt_sqlite/qt_sqlite_command.cpp \
    qt_sqlite/qt_data_row.cpp \
    qt_sqlite/qt_data_parameter.cpp \
    dbmodule/data_adapter_ad.cpp \
    dbmodule/data_adapter_mr.cpp \
    logic/data_model_request.cpp \
    logic/data_model_ad.cpp \
    logic/data_model_mr.cpp \
    dbmodule/data_adapter_mediator.cpp \
    logic/data_model_mediator.cpp \
    dbmodule/data_adapter_request_category.cpp \
    logic/data_model_request_category.cpp \
    gui/combobox_request_category.cpp \
    gui/dialog_request_data.cpp \
    app/application_params.cpp \
    app/application.cpp \
    gui/renderer_request.cpp \
    gui/dialog_id_request.cpp \
    dbmodule/data_adapter_address.cpp \
    gui/dialog_address_list.cpp \
    logic/data_model_address.cpp \
    gui/listview_address.cpp \
    dbmodule/data_adapter_so.cpp \
    gui/dialog_period.cpp \
    gui/dialog_authorization.cpp \
    gui/combobox_declarant_type.cpp \
    dbmodule/data_adapter_declarant_type.cpp \
    logic/data_model_declarant_type.cpp

HEADERS  += \
    gui/main_window.h \
    logic/business_logic.h \
    gui/widget_central.h \
    gui/widget_card_view.h \
    gui/listview_request.h \
    gui/delegate_line_edit.h \
    gui/combobox_mr.h \
    gui/combobox_mediator.h \
    gui/combobox_ad.h \
    gui/widget_search_card.h \
    dbmodule/data_adapter_request.h \
    qt_sqlite/qt_sqlite_dbvalue.h \
    qt_sqlite/qt_sqlite_connection.h \
    qt_sqlite/qt_sqlite_command.h \
    qt_sqlite/qt_data_row.h \
    qt_sqlite/qt_data_parameter.h \
    dbmodule/data_adapter_ad.h \
    dbmodule/data_adapter_mr.h \
    logic/data_model_request.h \
    logic/data_model_ad.h \
    logic/data_model_mr.h \
    dbmodule/data_adapter_mediator.h \
    logic/data_model_mediator.h \
    dbmodule/data_adapter_request_category.h \
    logic/data_model_request_category.h \
    gui/combobox_request_category.h \
    gui/dialog_request_data.h \
    app/application_params.h \
    app/application.h \
    gui/renderer_request.h \
    gui/dialog_id_request.h \
    dbmodule/data_adapter_address.h \
    gui/dialog_address_list.h \
    logic/data_model_address.h \
    gui/listview_address.h \
    dbmodule/data_adapter_so.h \
    gui/dialog_period.h \
    gui/dialog_authorization.h \
    gui/combobox_declarant_type.h \
    dbmodule/data_adapter_declarant_type.h \
    logic/data_model_declarant_type.h

INCLUDEPATH += ./app \
				./dbmodule \
				./gui \
				./logic \
				./qt_sqlite

MOC_DIR = ./xmoc

OBJECTS_DIR = ./xobj

RCC_DIR = ./xrcc

RESOURCES += res/app.qrc

TRANSLATIONS += ts/strings_ru.ts

unix: {
LIBS += /usr/lib64/libsqlite3.so
}

#home desktop setiings
#win32: {
#INCLUDEPATH += J:/Qt/sqlite
#LIBS += J:/Qt/sqlite/sqlite3.dll
#RC_FILE = res/winres/app_icon.rc
#}

#home notebook setiings
win32: {
INCLUDEPATH += W:/sqlite3/include
LIBS += W:/sqlite3/sqlite3.dll
RC_FILE = res/winres/app_icon.rc
}
