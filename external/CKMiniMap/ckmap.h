#ifndef CKMAP_H
#define CKMAP_H


class CKMap {
public:
    CKMap( );

    void loadSLD( char * );

    void drawMap( );

private:
    void loadGeoJSON( char *path );
};

#endif // CKMAP_H
