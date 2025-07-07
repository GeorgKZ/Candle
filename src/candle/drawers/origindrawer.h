#ifndef ORIGINDRAWER_H
#define ORIGINDRAWER_H

#include "shaderdrawable.h"

class OriginDrawer : public ShaderDrawable
{
public:

    OriginDrawer();

    virtual ~OriginDrawer() override;

protected:

    virtual bool updateData() override;
};

#endif // ORIGINDRAWER_H
