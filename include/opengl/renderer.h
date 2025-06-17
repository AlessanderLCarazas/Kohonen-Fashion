#ifndef RENDERER_H
#define RENDERER_H

#include "../som/som.h"

void renderSOM(const SOM& som);
void load_bmu_mapping(const std::string& filename);
void renderLegend();

#endif
