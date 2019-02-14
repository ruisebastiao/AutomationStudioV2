

include($$PROJECT_PATH/versioning/gitversion.pri)

SYM_DIR=$$shell_path($$PROJECT_PATH/breakpad/$${GIT_VERSION})


#win32:QMAKE_POST_LINK += $$quote(mkdir $$quote($$SYM_DIR) $$escape_expand(\n\t))

#QMAKE_POST_LINK += $$quote( if not exists $${SYM_DIR} mkdir $${SYM_DIR} $$escape_expand(\n\t))

#win32:QMAKE_POST_LINK += $$quote(RMDIR /S /Q $$SYM_DIR && mkdir $$SYM_DIR $$escape_expand(\n\t))

SYM_TARGET=$$SYM_DIR/$${TARGET}.sym

PDB_PATH= $${DESTDIR}/$${TARGET}.pdb

message(Symbols target:$$SYM_TARGET)

message(PDB path:$$PDB_PATH)

win32{
    CONFIG += skip_target_version_ext
}


QMAKE_POST_LINK += $$quote( $$PROJECT_PATH\breakpad\dump_syms.exe $$PDB_PATH > $$SYM_TARGET  $$escape_expand(\n\t))

