#include "filter_pipeline.h"

void FilterPipeline::AddFilter(std::unique_ptr<Filter> filter) {
    filters_.push_back(std::move(filter));
}

void FilterPipeline::Apply(Image& image) const {
    for (const std::unique_ptr<Filter>& filter : filters_) {
        filter->Apply(image);
    }
}
