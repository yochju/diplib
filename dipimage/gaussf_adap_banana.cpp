/*
 * DIPimage 3.0
 * This MEX-file implements the `gaussf_adap_banana` function
 *
 * (c)2018, Cris Luengo.
 * Based on original DIPlib code: (c)1995-2014, Delft University of Technology.
 * Based on original DIPimage code: (c)1999-2014, Delft University of Technology.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "dip_matlab_interface.h"
#include "diplib/analysis.h"
#include "diplib/nonlinear.h"

void mexFunction( int /*nlhs*/, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
   try {

      DML_MIN_ARGS( 1 );

      dip::Image const in = dml::GetImage( prhs[ 0 ] );
      dip::uint nDims = in.Dimensionality();
      DIP_THROW_IF( nDims != 2, dip::E::DIMENSIONALITY_NOT_SUPPORTED );

      int index = 1;
      dip::ImageArray params;
      if(( nrhs < 2 ) || mxIsEmpty( prhs[ 1 ] )) {
         // Compute orientation
         params = StructureTensorAnalysis( StructureTensor( in ), { "orientation", "curvature" } );
         ++index;
      } else if( mxIsCell( prhs[ 1 ] )) {
         // It's a params_im
         params = dml::GetImageArray( prhs[ 1 ] );
         ++index;
      } else {
         // It's orien_im, curv_im, {scale_im}
         DML_MIN_ARGS( 3 );
         params.resize( 2 );
         params[ 0 ] = dml::GetImage( prhs[ 1 ] );
         params[ 1 ] = dml::GetImage( prhs[ 2 ] );
         index += 2;
         // Is there a scaling image?
         if(( nrhs > index ) && !( mxIsDouble( prhs[ index ] ) && ( mxGetNumberOfElements( prhs[ index ] ) <= 2 ))) {
            params.emplace_back( dml::GetImage( prhs[ 3 ] ));
            ++index;
         }
      }

      DML_MAX_ARGS( index + 4 );

      dip::FloatArray sigmas = { 2.0, 0.0 };
      if( nrhs > index ) {
         sigmas = dml::GetFloatArray( prhs[ index ] );
         ++index;
      }

      dip::UnsignedArray order = { 0 };
      if( nrhs > index ) {
         order = dml::GetUnsignedArray( prhs[ index ] );
         ++index;
      }

      dip::UnsignedArray exponents = { 0 };
      if( nrhs > index ) {
         exponents = dml::GetUnsignedArray( prhs[ index ] );
         ++index;
      }

      dip::dfloat truncation = 2.0;
      if( nrhs > index ) {
         truncation = dml::GetFloat( prhs[ index ] );
      }

      dml::MatlabInterface mi;
      dip::Image out = mi.NewImage();

      dip::AdaptiveBanana( in, dip::CreateImageConstRefArray( params ), out, sigmas, order, truncation, exponents );

      plhs[ 0 ] = dml::GetArray( out );

   } catch( const dip::Error& e ) {
      mexErrMsgTxt( e.what() );
   }
}
