#include "gen-random-seq.h"
#include <iostream>
#include "pr-sim.h"

// unifrom distribution is default
// use no locality properties which is not actually happened in computer system
void gen_ref_seq(int range_min, int range_max, std::vector<int> &rseq) 
{
    std::random_device rd;
    std::default_random_engine e1(rd());
    std::uniform_int_distribution<int> uniform_dist(range_min, range_max);
    for (int i = 0; i < rseq.size(); i++) {
        rseq[i] = uniform_dist(e1);
    }
}
void gen_ref_seq(struct context *ctx) 
{
    switch (ctx->distribution) {
        case DISTRIB_NORMAL:
            gen_normal(ctx);
            break;
        case DISTRIB_UNIFORM:
            gen_uniform(ctx);
            break;
        case DISTRIB_BINOMIAL:
            gen_binomial(ctx);
            break;
        case DISTRIB_GEOMETRIC:
            gen_geometric(ctx);
            break;
        case DISTRIB_POISSON:
            gen_poisson(ctx);
            break;
        case DISTRIB_EXPONENTIAL:
            gen_exponential(ctx);
            break;
        case DISTRIB_GAMMA:
            gen_gamma(ctx);
            break;
        default:
            std::cerr 
                << "Error(Wrong distribution code) > "
                << ctx->distribution  << "\n";
            break;
    }
}

void gen_uniform(struct context *ctx)
{
    std::uniform_int_distribution<int>
        uniform_dist(ctx->npage_min, ctx->npage_max);
    std::random_device rd;
    std::default_random_engine e1(rd());

    int sz = ctx->ref_seqeunce.size();

    for (int i = 0; i < sz; i++) {
        ctx->ref_seqeunce[i] = uniform_dist(e1);
    }
}

void gen_normal(struct context *ctx)
{
    std::normal_distribution<double> normal_dist(ctx->mean, ctx->stddev);
    std::random_device rd;
    std::default_random_engine e1(rd());

    int cnt = 0;

    while (cnt < (ctx->ref_seqeunce).size()) {
        double ran = normal_dist(e1);

        if (ran >= ctx->npage_min && ran <= ctx->npage_max) {
            ctx->ref_seqeunce[cnt] = (int)ran;
            ++cnt;
        } else {
            continue;
        }
    }
}

/* This distribution produces random integers where each value represents a specific count of independent events occurring within a fixed interval, based on the observed mean rate at which they appear to happen (μ). */
void gen_poisson(struct context *ctx) 
{
    std::poisson_distribution<int> poisson_dist(ctx->mean);
    std::random_device rd;
    std::default_random_engine e1(rd());

    int sz = ctx->ref_seqeunce.size();
    int cnt = 0;

    while (cnt < sz) {
        double ran = poisson_dist(e1);

        if (ran >= ctx->npage_min && ran <= ctx->npage_max) {
            ctx->ref_seqeunce[cnt++] = (int)ran;
            continue;
        }

    }
}

/* This distribution produces random numbers where each value represents the interval between two random events that are independent but statistically defined by a constant average rate of occurrence (its lambda, λ). */
void gen_geometric(struct context *ctx)
{
    std::geometric_distribution<int> geometric_dist(ctx->mean);
    std::random_device rd;
    std::default_random_engine e1(rd());

    int sz = ctx->ref_seqeunce.size();
    int cnt = 0;

    while (cnt < sz) {
        double ran = geometric_dist(e1);

        if (ran >= ctx->npage_min && ran <= ctx->npage_max) {
            ctx->ref_seqeunce[cnt++] = (int)ran;
            continue;
        } 
    }
}

/* This distribution produces random integers in the range [0,t], where each value represents the number of successes in a sequence of t trials (each with a probability of success equal to p). */
void gen_binomial(struct context *ctx)
{
    /* number of experiments */
    int ntrial = ctx->npage_max - ctx->npage_min + 1;
    std::cout << "ntrial : " << ntrial << "\n";
    std::binomial_distribution<int> binomial_dist(ntrial, ctx->mean);
    std::random_device rd;
    std::default_random_engine e1(rd());

    int sz = ctx->ref_seqeunce.size();
    int cnt = 0;
    std::cout << "mean : " << ctx->mean << "\n";

    while (cnt < 100) {
        /* double ran = binomial_dist(e1) + ctx->npage_min; */
        double ran = binomial_dist(e1);
        /* std::cout << ran << "\n"; */
        if (ran >= ctx->npage_min && ran <= ctx->npage_max) {
            ctx->ref_seqeunce[cnt++] = (int)ran;
            continue;
        } 
        ++cnt;

    }
}


/* This distribution produces random numbers where each value represents the interval between two random events that are independent but statistically defined by a constant average rate of occurrence (its lambda, λ). */
void gen_exponential(struct context *ctx)
{
    std::exponential_distribution<double> exponential_dist(ctx->mean);
    std::random_device rd;
    std::default_random_engine e1(rd());

    int sz = ctx->ref_seqeunce.size();
    int cnt = 0;

    while (cnt < sz) {
        double ran = 1/exponential_dist(e1);
        if (ran >= ctx->npage_min && ran <= ctx->npage_max) {
            ctx->ref_seqeunce[cnt++] = (int)ran;
            continue;
        }
    }
}

void gen_gamma(struct context *ctx) 
{

}
