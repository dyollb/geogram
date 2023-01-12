/*
 *  Copyright (c) 2000-2022 Inria
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *  this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *  this list of conditions and the following disclaimer in the documentation
 *  and/or other materials provided with the distribution.
 *  * Neither the name of the ALICE Project-Team nor the names of its
 *  contributors may be used to endorse or promote products derived from this
 *  software without specific prior written permission.
 * 
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *
 *  Contact: Bruno Levy
 *
 *     https://www.inria.fr/fr/bruno-levy
 *
 *     Inria,
 *     Domaine de Voluceau,
 *     78150 Le Chesnay - Rocquencourt
 *     FRANCE
 *
 */

#ifndef GEOGRAM_MESH_TRIANGLE_INTERSECTION
#define GEOGRAM_MESH_TRIANGLE_INTERSECTION

#include <geogram/basic/common.h>
#include <geogram/basic/geometry.h>
#include <geogram/basic/memory.h>
#include <utility>

/**
 * \file geogram/mesh/triangle_intersection.h
 * \brief Symbolic computation of triangle-triangle intersection
 */

namespace GEO {

    /**
     * \brief Encodes the location of a point within a triangle.
     * \details A point can be located in 6 different regions, that
     * correspond to the three vertices, three edges and interior
     * of a triangle.
     *   - RGN_P0, RGN_P1, RGN_P2 when point is exactly on a vertex
     *   - RGN_E0, RGN_E1, RGN_E2 when point is on an edge
     *   - RGN_T when point is on the interior of the triangle
     */
    enum TriangleRegion {
        T1_RGN_P0 = 0,  
        T1_RGN_P1 = 1,  
        T1_RGN_P2 = 2,

        T2_RGN_P0 = 3,  
        T2_RGN_P1 = 4,  
        T2_RGN_P2 = 5,  
        
        T1_RGN_E0 = 6,  
        T1_RGN_E1 = 7,  
        T1_RGN_E2 = 8,

        T2_RGN_E0 = 9,  
        T2_RGN_E1 = 10, 
        T2_RGN_E2 = 11, 
        
        T1_RGN_T  = 12, 
        T2_RGN_T  = 13,
        
        T_RGN_NB  = 14
    };

    /**
     * \brief Encodes the symbolic representation of a triangle intersection,
     *  as a pair of TriangleRegion.
     */
    typedef std::pair<TriangleRegion, TriangleRegion> TriangleIsect;

    /**
     * \brief Triangle-triangle intersection
     * \details The input triangles are supposed to be non-degenerate
     *  (their three vertices are supposed to be distinct and not co-linear).
     *  For now, when intersection is surfacic (overlapping pair
     *  of co-planar triangles), the vertices of the intersection are 
     *  not sorted. One can order them by computing their convex hull.
     * \param[in] p0 , p1 , p2 first triangle
     * \param[in] q0 , q1 , q2 second triangle
     * \param[out] result the intersection in symbolic
     *  form, as TriangleRegion pairs. There can be
     *  between 0 and 6 intersection pairs in the result.
     * \retval true if there is a non-degenerate intersection
     * \retval false otherwise. Degenerate intersection cases are:
     *  - one vertex in common
     *  - two vertices (an edge) in common
     *  - or duplicated triangles.
     */
    bool GEOGRAM_API triangles_intersections(
        const vec3& p0, const vec3& p1, const vec3& p2,
        const vec3& q0, const vec3& q1, const vec3& q2,
        vector<TriangleIsect>& result
    );


    /**
     * \brief Triangle-triangle intersection
     * \param[in] p0 , p1 , p2 first triangle
     * \param[in] q0 , q1 , q2 second triangle
     * \retval true if there is a non-degenerate intersection
     * \retval false otherwise. Degenerate intersection cases are:
     *  - one vertex in common
     *  - two vertices (an edge) in common
     *  - or duplicated triangles.
     */
    inline bool triangles_intersections(
        const vec3& p0, const vec3& p1, const vec3& p2,
        const vec3& q0, const vec3& q1, const vec3& q2
        
    ) {
        vector<TriangleIsect> result;        
        return triangles_intersections(p0,p1,p2,q0,q1,q2,result);
    }
    
    /**
     * \brief Converts a triangle region code to a string.
     * \param[in] rgn the triangle region code.
     * \return the string representation of \p rgn.
     */
    std::string GEOGRAM_API region_to_string(TriangleRegion rgn);
    
    /**
     * \brief Prints a triangle intersection element to a stream.
     * \details Used for debugging purposes.
     * \param[in] out the stream.
     * \param[in] I the intersection element to be printed.
     */
    inline std::ostream& operator<<(
	std::ostream& out, const TriangleIsect& I
    ) {
	return (
	    out << "("
	    << region_to_string(I.first) << ","
	    << region_to_string(I.second)
	    << ")"
	);
    }
    
    /**
     * \brief Prints the result of a triangle intersection to a stream.
     * \details Used for debugging purposes.
     * \param[in] out the stream.
     * \param[in] II the intersections to be printed.
     */
    inline std::ostream& operator<<(
	std::ostream& out, vector<TriangleIsect>& II
    ) {
	for(index_t i=0; i<II.size(); ++i) {
	    out << II[i] << " ";
	}
	return out;
    }
}

#endif

