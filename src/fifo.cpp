#include "pr-sim.h"
#include "gen-random-seq.h"
#include <list>
#include <vector>
#include <algorithm>
#include <queue>

int FIFO::count_page_fault(struct context *ctx) {
    std::list<int> loaded_pages;
    int nfault = 0;

    for (auto &page : ctx->ref_seqeunce) {
        auto has_page = !(std::find(loaded_pages.begin(), loaded_pages.end(), page) == loaded_pages.end());
        if (has_page == false) {
            ++nfault;
            if (loaded_pages.size() >= ctx->available_frames) {
                loaded_pages.pop_front();
            }
            loaded_pages.push_back(page);
        }
    }
    return nfault;
}
