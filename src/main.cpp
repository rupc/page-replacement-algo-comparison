#include <iostream>
#include <map>
#include <set>
#include <cassert>
#include "pr-sim.h"
#include <getopt.h>
#include <vector>

template<typename T>
void print_vec(std::vector<T> &v) {
    for (auto &p : v) 
        std::cout << p << " ";
    std::cout << "\n";

}
template<typename T>
void print_maptable(std::map<T, T> &tab) {
    for (auto &p : tab) {
        std::cout << p.first << " " << p.second << "\n";
    }
}
template<typename T>
void print_set(std::set<T> &s) {
    std::cout << "Loaded pages : ";
    for (auto &p : s) {
        std::cout << p << " ";
    }
}
int main(int argc, char *argv[])
{
    int npage_min = 0;
    int npage_max = 9;
    int nref = 30; // number of reference sequence
    int available_frames = 7;
    struct context ictx(npage_min, npage_max, nref, available_frames);
    get_context(&ictx, argc, argv); // process option variables
    ictx.print();
    LRU lru;
    int lru_fault = lru.count_page_fault(&ictx);
    std::cout << "LRU's fault " << lru_fault << "\n";
}
// return recently referenced page
int reference_next_page(int page, std::map<int, int> &tab) {
    return (tab[page]++);
}
void get_context(struct context *ctx, int argc, char *argv []) {
    int choice;
    while (1)
    {
        static struct option long_options[] =
        {
            /* Use flags like so:
            {"verbose",    no_argument,    &verbose_flag, 'V'}*/
            /* Argument styles: no_argument, required_argument, optional_argument */
            {"version", no_argument,    0,    'v'},
            {"help", no_argument,    0,    'h'},
            {"num-frames", required_argument,    0,    'f'},
            {"min-page", required_argument,    0,    'm'},
            {"max-page", required_argument,    0,    'M'},
            {"num-references", required_argument,    0,    'r'},
            
            {0,0,0,0}
        };

        int option_index = 0;

        /* Argument parameters:
            no_argument: " "
            required_argument: ":"
            optional_argument: "::" */

        choice = getopt_long(argc, argv, "vhf:M:m:r:",
                    long_options, &option_index);

        if (choice == -1)
            break;

        switch( choice )
        {
            case 'v':
                std::cout << "version fun" << "\n";
                break;
            case 'h':
                std::cout << "help fun" << "\n";
                break;
            case 'f':
                std::cout << "frames : " <<  atoi(optarg) << "\n";
                
                break;
            case 'M':
                std::cout << "max-page : " <<  atoi(optarg) << "\n";
                break;
            case 'm':
                std::cout << "min-page : " <<  atoi(optarg) << "\n";
                break;
            case 'r':
                std::cout << "num-reference : " <<  atoi(optarg) << "\n";
                break;
            case '?':
                /* getopt_long will have already printed an error */
                std::cout << "WTF?" << "\n";
                break;
            default:
                /* Not sure how to get here... */
                //return EXIT_FAILURE;
                break;
        }
    }

    /* Deal with non-option arguments here */
    if ( optind < argc )
    {
        while ( optind < argc )
        {
            
        }
    }
}
