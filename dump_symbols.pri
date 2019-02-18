CONFIG += skip_target_version_ext

win32{



include($$PROJECT_PATH/versioning/gitversion.pri)

SYM_DIR=$$shell_path($$PROJECT_PATH/breakpad/$${GIT_VERSION})


#win32:QMAKE_POST_LINK += $$quote(mkdir $$quote($$SYM_DIR) $$escape_expand(\n\t))

#QMAKE_POST_LINK += $$quote( if not exists $${SYM_DIR} mkdir $${SYM_DIR} $$escape_expand(\n\t))

#win32:QMAKE_POST_LINK += $$quote(RMDIR /S /Q $$SYM_DIR && mkdir $$SYM_DIR $$escape_expand(\n\t))

SYM_TARGET=$$SYM_DIR/$${TARGET}.sym
message(Symbols target:$$SYM_TARGET)

win32{
    PDB_PATH= $${DESTDIR}/$${TARGET}.pdb
    message(PDB path:$$PDB_PATH)
    QMAKE_POST_LINK += $$quote( $$PROJECT_PATH\breakpad\dump_syms.exe $$PDB_PATH > $$SYM_TARGET  $$escape_expand(\n\t))

}


unix{
    TARGET_PATH= $${DEPLOY_PATH}/$${TARGET}.$${QMAKE_EXTENSION_SHLIB}
    message(Symbols source:$$TARGET_PATH)
    QMAKE_POST_LINK += $$quote( dump_syms.exe $$TARGET_PATH > $$SYM_TARGET  $$escape_expand(\n\t))

}

}
#win32{
#}



