#ifndef EMBED_H
#define EMBED_H

#include "utils.h"
#include "state.h"

namespace Embed
{
    VS build(VD& xvals, VD& tvals, double tau, int m);
}

#endif // EMBED_H
