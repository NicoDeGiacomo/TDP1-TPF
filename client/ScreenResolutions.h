//
// Created by ale on 8/12/21.
//

#ifndef QUANTUM_CHESS_SCREENRESOLUTIONS_H
#define QUANTUM_CHESS_SCREENRESOLUTIONS_H

namespace ScreenResolutions {
    struct Resolution {
        int width;
        int height;
    };
    const int resolutionsCount = 6;
    const Resolution nHD {640,360};
    const Resolution SVGA {800,600};
    const Resolution WXGA {1280,720};
    const Resolution SXGA {1280,1024};
    const Resolution WXGA_PLUS {1440,900};
    const Resolution FHD {1920,1080};
}


#endif //QUANTUM_CHESS_SCREENRESOLUTIONS_H
