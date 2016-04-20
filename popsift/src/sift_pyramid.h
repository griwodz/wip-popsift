#pragma once

#include <iostream>

#include "s_image.h"
#include "sift_conf.h"
#include "sift_extremum.h"
#include "sift_extrema_mgmt.h"
#include "sift_octave.h"

namespace popart {

class Pyramid
{
    int     _num_octaves;
    int     _levels;
    Octave* _octaves;
    int     _gauss_group;

    Config::ScalingMode _scaling_mode;

public:
    Pyramid( Config& config,
             Image*  base,
             int     w,
             int     h );
    ~Pyramid( );

    void find_extrema( Image* base );

    void download_and_save_array( const char* basename, uint32_t octave, uint32_t level );

    void download_descriptors( uint32_t octave );
    void save_descriptors( const char* basename, uint32_t octave, int downscale_factor );


    inline int getNumOctaves() const { return _num_octaves; }
    inline int getNumLevels()  const { return _levels; }

private:
    void build_v11 ( Image* base );

    inline void horiz_from_upscaled_orig_tex( cudaTextureObject_t src_data, int octave );
    inline void downscale_from_prev_octave( int octave, int level );
    inline void downscale_from_prev_octave_and_horiz_blur( int octave, int level );
    inline void horiz_from_prev_level( int octave, int level );
    inline void vert_from_interm( int octave, int level );
    inline void dog_from_blurred( int octave, int level );

    void reset_extrema_mgmt( );
    void find_extrema_v6( );

    template<int HEIGHT>
    void find_extrema_v6_sub( );

    void orientation_v1( );

    void descriptors_v1( );

    void test_last_error( int line );
    void debug_out_floats  ( float* data, uint32_t pitch, uint32_t height );
    void debug_out_floats_t( float* data, uint32_t pitch, uint32_t height );
};

} // namespace popart
