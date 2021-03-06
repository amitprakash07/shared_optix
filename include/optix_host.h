
/*
 * Copyright (c) 2008 - 2009 NVIDIA Corporation.  All rights reserved.
 *
 * NVIDIA Corporation and its licensors retain all intellectual property and proprietary
 * rights in and to this software, related documentation and any modifications thereto.
 * Any use, reproduction, disclosure or distribution of this software and related
 * documentation without an express license agreement from NVIDIA Corporation is strictly
 * prohibited.
 *
 * TO THE MAXIMUM EXTENT PERMITTED BY APPLICABLE LAW, THIS SOFTWARE IS PROVIDED *AS IS*
 * AND NVIDIA AND ITS SUPPLIERS DISCLAIM ALL WARRANTIES, EITHER EXPRESS OR IMPLIED,
 * INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE.  IN NO EVENT SHALL NVIDIA OR ITS SUPPLIERS BE LIABLE FOR ANY
 * SPECIAL, INCIDENTAL, INDIRECT, OR CONSEQUENTIAL DAMAGES WHATSOEVER (INCLUDING, WITHOUT
 * LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION, LOSS OF
 * BUSINESS INFORMATION, OR ANY OTHER PECUNIARY LOSS) ARISING OUT OF THE USE OF OR
 * INABILITY TO USE THIS SOFTWARE, EVEN IF NVIDIA HAS BEEN ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGES
 */

/**
 * @file   optix_host.h
 * @author NVIDIA Corporation
 * @brief  OptiX public API
 *
 * OptiX public API Reference - Host side
 */

#ifndef __optix_optix_host_h__
#define __optix_optix_host_h__

#ifndef RTAPI
#if defined( _WIN32 )
#define RTAPI __declspec(dllimport)
#else
#define RTAPI
#endif
#endif

#include "internal/optix_declarations.h"


/************************************
 **
 **    Platform-Dependent Types
 **
 ***********************************/

#if defined( _WIN64 )
typedef unsigned __int64    RTsize;
#elif defined( _WIN32 )
typedef unsigned int        RTsize;
#else
typedef long unsigned int   RTsize;
#endif

/************************************
 **
 **    Opaque Object Types
 **
 ***********************************/
 
/** Opaque type to handle Acceleration Structures - Note that the *_api type should never be used directly. 
Only the typedef target name will be guaranteed to remain unchanged */
typedef struct RTacceleration_api       * RTacceleration;
/** Opaque type to handle Buffers - Note that the *_api type should never be used directly. 
Only the typedef target name will be guaranteed to remain unchanged */
typedef struct RTbuffer_api             * RTbuffer;
/** Opaque type to handle Contexts - Note that the *_api type should never be used directly. 
Only the typedef target name will be guaranteed to remain unchanged */
typedef struct RTcontext_api            * RTcontext;
/** Opaque type to handle Geometry - Note that the *_api type should never be used directly. 
Only the typedef target name will be guaranteed to remain unchanged */
typedef struct RTgeometry_api           * RTgeometry;
/** Opaque type to handle Geometry Instance - Note that the *_api type should never be used directly. 
Only the typedef target name will be guaranteed to remain unchanged */
typedef struct RTgeometryinstance_api   * RTgeometryinstance;
/** Opaque type to handle Geometry Group - Note that the *_api type should never be used directly. 
Only the typedef target name will be guaranteed to remain unchanged */
typedef struct RTgeometrygroup_api      * RTgeometrygroup;
/** Opaque type to handle Group - Note that the *_api type should never be used directly. 
Only the typedef target name will be guaranteed to remain unchanged */
typedef struct RTgroup_api              * RTgroup;
/** Opaque type to handle Material - Note that the *_api type should never be used directly. 
Only the typedef target name will be guaranteed to remain unchanged */
typedef struct RTmaterial_api           * RTmaterial;
/** Opaque type to handle Program - Note that the *_api type should never be used directly. 
Only the typedef target name will be guaranteed to remain unchanged */
typedef struct RTprogram_api            * RTprogram;
/** Opaque type to handle Selector - Note that the *_api type should never be used directly. 
Only the typedef target name will be guaranteed to remain unchanged */
typedef struct RTselector_api           * RTselector;
/** Opaque type to handle Texture Sampler - Note that the *_api type should never be used directly. 
Only the typedef target name will be guaranteed to remain unchanged */
typedef struct RTtexturesampler_api     * RTtexturesampler;
/** Opaque type to handle Transform - Note that the *_api type should never be used directly. 
Only the typedef target name will be guaranteed to remain unchanged */
typedef struct RTtransform_api          * RTtransform;
/** Opaque type to handle Variable - Note that the *_api type should never be used directly. 
Only the typedef target name will be guaranteed to remain unchanged */
typedef struct RTvariable_api           * RTvariable;
/** Opaque type to handle Object - Note that the *_api type should never be used directly. 
Only the typedef target name will be guaranteed to remain unchanged */
typedef void                            * RTobject;

/************************************
 **
 **    Callback Function Types
 **
 ***********************************/

/** Callback signature for use with rtContextSetTimeoutCallback.
 * Return 1 to ask for abort, 0 to continue. */
typedef int (*RTtimeoutcallback)(void);


#ifdef __cplusplus
extern "C" {
#endif

/************************************
 **
 **    Context-free functions
 **
 ***********************************/

  /**
  * @brief Returns the current OptiX version
  * 
  * @ingroup ContextFreeFunctions
  * 
  * <B>Description</B>
  * 
  * @ref rtGetVersion returns in \a version a numerically comparable
  * version number of the current OptiX library.
  * 
  * @param[out]  version   OptiX version number
  * 
  * <B>Return values</B>
  * 
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtGetVersion was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtDeviceGetDeviceCount
  * 
  */
  RTresult RTAPI rtGetVersion(unsigned int* version);
  
  /**
  * @brief Returns the number of OptiX capable devices
  * 
  * @ingroup ContextFreeFunctions
  * 
  * <B>Description</B>
  * 
  * @ref rtDeviceGetDeviceCount returns in \a count the number of compute
  * devices that are available in the host system and will be used by
  * OptiX.
  * 
  * @param[out]  count   Number devices available for OptiX
  * 
  * <B>Return values</B>
  * 
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtDeviceGetDeviceCount was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtGetVersion
  * 
  */
  RTresult RTAPI rtDeviceGetDeviceCount(unsigned int* count);
  
  /**
  * @brief Returns an attribute specific to an OptiX device
  * 
  * @ingroup ContextFreeFunctions
  * 
  * <B>Description</B>
  * 
  * @ref rtDeviceGetAttribute returns in \a p the value of the per device attribute
  * specified by \a attrib for device \a ordinal.
  * 
  * Each attribute can have a different size.  The sizes are given in the following list:
  * 
  *   - @ref RT_DEVICE_ATTRIBUTE_MAX_THREADS_PER_BLOCK        sizeof(int)
  *   - @ref RT_DEVICE_ATTRIBUTE_CLOCK_RATE                   sizeof(int)
  *   - @ref RT_DEVICE_ATTRIBUTE_MULTIPROCESSOR_COUNT         sizeof(int)
  *   - @ref RT_DEVICE_ATTRIBUTE_EXECUTION_TIMEOUT_ENABLED    sizeof(int)
  *   - @ref RT_DEVICE_ATTRIBUTE_MAX_HARDWARE_TEXTURE_COUNT   sizeof(int)
  *   - @ref RT_DEVICE_ATTRIBUTE_NAME                         up to size-1
  *   - @ref RT_DEVICE_ATTRIBUTE_COMPUTE_CAPABILITY           sizeof(int2)
  *   - @ref RT_DEVICE_ATTRIBUTE_TOTAL_MEMORY                 sizeof(RTsize)
  *   - @ref RT_DEVICE_ATTRIBUTE_TCC_DRIVER                   sizeof(int)
  *   - @ref RT_DEVICE_ATTRIBUTE_CUDA_DEVICE_ORDINAL          sizeof(int)
  * 
  * @param[in]   ordinal   OptiX device ordinal
  * @param[in]   attrib    Attribute to query
  * @param[in]   size      Size of the attribute being queried.  Parameter \a p must have at least this much memory backing it
  * @param[out]  p         Return pointer where the value of the attribute will be copied into.  This must point to at least \a size bytes of memory
  * 
  * <B>Return values</B>
  * 
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE - Can be returned if size does not match the proper size of the attribute, if \a p is
  * \a NULL, or if \a ordinal does not correspond to an OptiX device
  * 
  * <B>History</B>
  * 
  * @ref rtDeviceGetAttribute was introduced in OptiX 2.0.
  * @ref RT_DEVICE_ATTRIBUTE_TCC_DRIVER was introduced in OptiX 3.0.
  * @ref RT_DEVICE_ATTRIBUTE_CUDA_DEVICE_ORDINAL was introduced in OptiX 3.0.
  * 
  * <B>See also</B>
  * @ref rtDeviceGetDeviceCount,
  * @ref rtContextGetAttribute
  * 
  */
  RTresult RTAPI rtDeviceGetAttribute(int ordinal, RTdeviceattribute attrib, RTsize size, void* p);
  

/************************************
 **
 **    Object Variable Accessors
 **
 ***********************************/

  /* Sets */
  /** 
  * @ingroup rtVariableSet Variable setters
  *    
  * @brief Functions designed to modify the value of a program variable
  * 
  * <B>Description</B>
  * 
  * @ref rtVariableSet functions modify the value of a program variable or variable array. The
  * target variable is specificed by \a variable, which should be a value returned by
  * @ref rtContextGetVariable.
  *
  * The commands \a rtVariableSet{1-2-3-4}{f-i-ui}v are used to modify the value of a
  * program variable specified by \a variable using the values passed as arguments.
  * The number specified in the command should match the number of components in
  * the data type of the specified program variable (e.g., 1 for float, int,
  * unsigned int; 2 for float2, int2, uint2, etc.). The suffix \a f indicates
  * that \a variable has floating point type, the suffix \a i indicates that
  * \a variable has integral type, and the suffix \a ui indicates that that
  * \a variable has unsigned integral type. The \a v variants of this function
  * should be used to load the program variable's value from the array specified by
  * parameter \a v. In this case, the array \a v should contain as many elements as
  * there are program variable components.
  *
  * The commands \a rtVariableSetMatrix{2-3-4}x{2-3-4}fv are used to modify the value
  * of a program variable whose data type is a matrix. The numbers in the command
  * names are the number of rows and columns, respectively. 
  * For example, \a 2x4 indicates a matrix with 2 rows and 4 columns (i.e., 8 values). 
  * If \a transpose is \a 0, the matrix is specified in row-major order, otherwise
  * in column-major order or, equivalently, as a matrix with the number of rows and
  * columns swapped in row-major order.
  *
  * If \a variable is not a valid variable, these calls have no effect and return
  * @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  *
  * @ref rtVariableSet were introduced in OptiX 1.0.
  *
  * <B>See also</B>
  * @ref rtVariableGet,
  * @ref rtVariableSet,
  * @ref rtDeclareVariable
  *
  * @{
  */
  /**
  * @param[in]   v          Specifies the program variable to be modified
  * @param[in]   f1         Specifies the new float value of the program variable
  */
  RTresult RTAPI rtVariableSet1f(RTvariable v, float f1);

  /**
  * @param[in]   v          Specifies the program variable to be modified
  * @param[in]   f1         Specifies the new float value of the program variable
  * @param[in]   f2         Specifies the new float value of the program variable
  */
  RTresult RTAPI rtVariableSet2f(RTvariable v, float f1, float f2);
  
  /**
  * @param[in]   v          Specifies the program variable to be modified
  * @param[in]   f1         Specifies the new float value of the program variable
  * @param[in]   f2         Specifies the new float value of the program variable
  * @param[in]   f3         Specifies the new float value of the program variable
  */
  RTresult RTAPI rtVariableSet3f(RTvariable v, float f1, float f2, float f3);
  
  /**
  * @param[in]   v          Specifies the program variable to be modified
  * @param[in]   f1         Specifies the new float value of the program variable
  * @param[in]   f2         Specifies the new float value of the program variable
  * @param[in]   f3         Specifies the new float value of the program variable
  * @param[in]   f4         Specifies the new float value of the program variable
  */
  RTresult RTAPI rtVariableSet4f(RTvariable v, float f1, float f2, float f3, float f4);
  
  /**
  * @param[in]   v          Specifies the program variable to be modified
  * @param[in]   f          Array of float values to set the variable to
  */
  RTresult RTAPI rtVariableSet1fv(RTvariable v, const float* f);
  
  /**
  * @param[in]   v          Specifies the program variable to be modified
  * @param[in]   f          Array of float values to set the variable to
  */
  RTresult RTAPI rtVariableSet2fv(RTvariable v, const float* f);
  
  /**
  * @param[in]   v          Specifies the program variable to be modified
  * @param[in]   f          Array of float values to set the variable to
  */
  RTresult RTAPI rtVariableSet3fv(RTvariable v, const float* f);
  
  /**
  * @param[in]   v          Specifies the program variable to be modified
  * @param[in]   f          Array of float values to set the variable to
  */
  RTresult RTAPI rtVariableSet4fv(RTvariable v, const float* f);

  /**
  * @param[in]   v          Specifies the program variable to be modified
  * @param[in]   i1         Specifies the new integer value of the program variable
  */
  RTresult RTAPI rtVariableSet1i(RTvariable v, int i1);
  
  /**
  * @param[in]   v          Specifies the program variable to be modified
  * @param[in]   i1         Specifies the new integer value of the program variable
  * @param[in]   i2         Specifies the new integer value of the program variable
  */
  RTresult RTAPI rtVariableSet2i(RTvariable v, int i1, int i2);
  
  /**
  * @param[in]   v          Specifies the program variable to be modified
  * @param[in]   i1         Specifies the new integer value of the program variable
  * @param[in]   i2         Specifies the new integer value of the program variable
  * @param[in]   i3         Specifies the new integer value of the program variable
  */
  RTresult RTAPI rtVariableSet3i(RTvariable v, int i1, int i2, int i3);
  
  /**
  * @param[in]   v          Specifies the program variable to be modified
  * @param[in]   i1         Specifies the new integer value of the program variable
  * @param[in]   i2         Specifies the new integer value of the program variable
  * @param[in]   i3         Specifies the new integer value of the program variable
  * @param[in]   i4         Specifies the new integer value of the program variable
  */
  RTresult RTAPI rtVariableSet4i(RTvariable v, int i1, int i2, int i3, int i4);
  
  /**
  * @param[in]   v          Specifies the program variable to be modified
  * @param[in]   i          Array of integer values to set the variable to
  */
  RTresult RTAPI rtVariableSet1iv(RTvariable v, const int* i);
  
  /**
  * @param[in]   v          Specifies the program variable to be modified
  * @param[in]   i          Array of integer values to set the variable to
  */
  RTresult RTAPI rtVariableSet2iv(RTvariable v, const int* i);
  
  /**
  * @param[in]   v          Specifies the program variable to be modified
  * @param[in]   i          Array of integer values to set the variable to
  */
  RTresult RTAPI rtVariableSet3iv(RTvariable v, const int* i);
  
  /**
  * @param[in]   v          Specifies the program variable to be modified
  * @param[in]   i          Array of integer values to set the variable to
  */
  RTresult RTAPI rtVariableSet4iv(RTvariable v, const int* i);

  /**
  * @param[in]   v          Specifies the program variable to be modified
  * @param[in]   u1         Specifies the new unsigned integer value of the program variable
  */
  RTresult RTAPI rtVariableSet1ui(RTvariable v, unsigned int u1);
  
  /**
  * @param[in]   v          Specifies the program variable to be modified
  * @param[in]   u1         Specifies the new unsigned integer value of the program variable
  * @param[in]   u2         Specifies the new unsigned integer value of the program variable
  */
  RTresult RTAPI rtVariableSet2ui(RTvariable v, unsigned int u1, unsigned int u2);
  
  /**
  * @param[in]   v          Specifies the program variable to be modified
  * @param[in]   u1         Specifies the new unsigned integer value of the program variable
  * @param[in]   u2         Specifies the new unsigned integer value of the program variable
  * @param[in]   u3         Specifies the new unsigned integer value of the program variable
  */
  RTresult RTAPI rtVariableSet3ui(RTvariable v, unsigned int u1, unsigned int u2, unsigned int u3);
  
  /**
  * @param[in]   v          Specifies the program variable to be modified
  * @param[in]   u1         Specifies the new unsigned integer value of the program variable
  * @param[in]   u2         Specifies the new unsigned integer value of the program variable
  * @param[in]   u3         Specifies the new unsigned integer value of the program variable
  * @param[in]   u4         Specifies the new unsigned integer value of the program variable
  */
  RTresult RTAPI rtVariableSet4ui(RTvariable v, unsigned int u1, unsigned int u2, unsigned int u3, unsigned int u4);
  
  /**
  * @param[in]   v          Specifies the program variable to be modified
  * @param[in]   u          Array of unsigned integer values to set the variable to
  */
  RTresult RTAPI rtVariableSet1uiv(RTvariable v, const unsigned int* u);
  
  /**
  * @param[in]   v          Specifies the program variable to be modified
  * @param[in]   u          Array of unsigned integer values to set the variable to
  */
  RTresult RTAPI rtVariableSet2uiv(RTvariable v, const unsigned int* u);
  
  /**
  * @param[in]   v          Specifies the program variable to be modified
  * @param[in]   u          Array of unsigned integer values to set the variable to
  */
  RTresult RTAPI rtVariableSet3uiv(RTvariable v, const unsigned int* u);
  
  /**
  * @param[in]   v          Specifies the program variable to be modified
  * @param[in]   u          Array of unsigned integer values to set the variable to
  */
  RTresult RTAPI rtVariableSet4uiv(RTvariable v, const unsigned int* u);

  /**
  * @param[in]   v          Specifies the program variable to be modified
  * @param[in]   transpose  Specifies row-major or column-major order
  * @param[in]   m          Array of float values to set the matrix to
  */
  RTresult RTAPI rtVariableSetMatrix2x2fv(RTvariable v, int transpose, const float* m);
  
  /**
  * @param[in]   v          Specifies the program variable to be modified
  * @param[in]   transpose  Specifies row-major or column-major order
  * @param[in]   m          Array of float values to set the matrix to
  */
  RTresult RTAPI rtVariableSetMatrix2x3fv(RTvariable v, int transpose, const float* m);
  
  /**
  * @param[in]   v          Specifies the program variable to be modified
  * @param[in]   transpose  Specifies row-major or column-major order
  * @param[in]   m          Array of float values to set the matrix to
  */
  RTresult RTAPI rtVariableSetMatrix2x4fv(RTvariable v, int transpose, const float* m);
  
  /**
  * @param[in]   v          Specifies the program variable to be modified
  * @param[in]   transpose  Specifies row-major or column-major order
  * @param[in]   m          Array of float values to set the matrix to
  */
  RTresult RTAPI rtVariableSetMatrix3x2fv(RTvariable v, int transpose, const float* m);
  
  /**
  * @param[in]   v          Specifies the program variable to be modified
  * @param[in]   transpose  Specifies row-major or column-major order
  * @param[in]   m          Array of float values to set the matrix to
  */
  RTresult RTAPI rtVariableSetMatrix3x3fv(RTvariable v, int transpose, const float* m);
  
  /**
  * @param[in]   v          Specifies the program variable to be modified
  * @param[in]   transpose  Specifies row-major or column-major order
  * @param[in]   m          Array of float values to set the matrix to
  */
  RTresult RTAPI rtVariableSetMatrix3x4fv(RTvariable v, int transpose, const float* m);
  
  /**
  * @param[in]   v          Specifies the program variable to be modified
  * @param[in]   transpose  Specifies row-major or column-major order
  * @param[in]   m          Array of float values to set the matrix to
  */
  RTresult RTAPI rtVariableSetMatrix4x2fv(RTvariable v, int transpose, const float* m);
  
  /**
  * @param[in]   v          Specifies the program variable to be modified
  * @param[in]   transpose  Specifies row-major or column-major order
  * @param[in]   m          Array of float values to set the matrix to
  */
  RTresult RTAPI rtVariableSetMatrix4x3fv(RTvariable v, int transpose, const float* m);
  
  /**
  * @param[in]   v          Specifies the program variable to be modified
  * @param[in]   transpose  Specifies row-major or column-major order
  * @param[in]   m          Array of float values to set the matrix to
  */
  RTresult RTAPI rtVariableSetMatrix4x4fv(RTvariable v, int transpose, const float* m);
  /**
  * @}
  */

  /**
  * @brief Sets a program variable value to a OptiX object
  * 
  * @ingroup Variables
  * 
  * <B>Description</B>
  * 
  * @ref rtVariableSetObject sets a program variable to an OptiX object value.  The target
  * variable is specified by \a variable. The new value of the program variable is
  * specified by \a object. The concrete type of \a object can be one of @ref RTbuffer,
  * @ref RTtexturesampler, @ref RTgroup, @ref RTprogram, @ref RTselector, @ref
  * RTgeometrygroup, or @ref RTtransform.  If \a variable is not a valid variable or \a
  * object is not a valid OptiX object, this call has no effect and returns @ref
  * RT_ERROR_INVALID_VALUE.
  * 
  * @param[in]   v          Specifies the program variable to be set
  * @param[in]   object     Specifies the new value of the program variable
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_TYPE_MISMATCH
  * 
  * <B>History</B>
  * 
  * @ref rtVariableSetObject was introduced in OptiX 1.0.  The ability to bind an @ref
  * RTprogram to a variable was intrduced in OptiX 3.0.
  * 
  * <B>See also</B>
  * @ref rtVariableGetObject,
  * @ref rtContextDeclareVariable
  * 
  */
  RTresult RTAPI rtVariableSetObject(RTvariable v, RTobject object);
  
  /**
  * @brief Defined
  * 
  * @ingroup Variables
  * 
  * <B>Description</B>
  * 
  * @ref rtVariableSetUserData modifies the value of a program variable whose data type is
  * user-defined. The value copied into the variable is defined by an arbitrary region of
  * memory, pointed to by \a ptr. The size of the memory region is given by \a size. The
  * target variable is specified by \a variable.  If \a variable is not a valid variable,
  * this call has no effect and returns @ref RT_ERROR_INVALID_VALUE.
  * 
  * @param[in]   v          Specifies the program variable to be modified
  * @param[in]   size       Specifies the size of the new value, in bytes
  * @param[in]   ptr        Specifies a pointer to the new value of the program variable
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * - @ref RT_ERROR_TYPE_MISMATCH
  * 
  * <B>History</B>
  * 
  * @ref rtVariableSetUserData was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtVariableGetUserData,
  * @ref rtContextDeclareVariable
  * 
  */
  RTresult RTAPI rtVariableSetUserData(RTvariable v, RTsize size, const void* ptr);
  

  /* Gets */
  /**
  * @ingroup rtVariableGet
  *    
  * @brief Functions designed to modify the value of a program variable
  * 
  * <B>Description</B>
  * 
  * @ref rtVariableGet functions return the value of a program variable or variable
  * array. The target variable is specificed by \a variable.
  *
  * The commands \a rtVariableGet{1-2-3-4}{f-i-ui}v are used to query the value
  * of a program variable specified by \a variable using the pointers passed as arguments
  * as return locations for each component of the vector-typed variable. The number
  * specified in the command should match the number of components in the data type
  * of the specified program variable (e.g., 1 for float, int, unsigned int; 2 for
  * float2, int2, uint2, etc.). The suffix \a f indicates that floating-point
  * values are expected to be returned, the suffix \a i indicates that integer
  * values are expected, and the suffix \a ui indicates that unsigned integer
  * values are expected, and this type should also match the data type of the
  * specified program variable. The \a f variants of this function should be used
  * to query values for program variables defined as float, float2, float3, float4,
  * or arrays of these. The \a i variants of this function should be used to
  * query values for program variables defined as int, int2, int3, int4, or
  * arrays of these. The \a ui variants of this function should be used to query
  * values for program variables defined as unsigned int, uint2, uint3, uint4,
  * or arrays of these. The \a v variants of this function should be used to
  * return the program variable's value to the array specified by parameter
  * \a v. In this case, the array \a v should be large enough to accomodate all
  * of the program variable's components.
  *
  * The commands \a rtVariableGetMatrix{2-3-4}x{2-3-4}fv are used to query the
  * value of a program variable whose data type is a matrix. The numbers in the
  * command names are interpreted as the dimensionality of the matrix. For example,
  * \a 2x4 indicates a 2 x 4 matrix with 2 columns and 4 rows (i.e., 8
  * values). If \a transpose is \a 0, the matrix is returned in row major order,
  * otherwise in column major order.
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtVariableGet were introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtVariableSet,
  * @ref rtVariableGetType,
  * @ref rtContextDeclareVariable
  *
  * @{ 
  */
  /**
  * @param[in]   v          Specifies the program variable whose value is to be returned
  * @param[in]   f1         Float value to be returned
  */
  RTresult RTAPI rtVariableGet1f(RTvariable v, float* f1);
  
  /**
  * @param[in]   v          Specifies the program variable whose value is to be returned
  * @param[in]   f1         Float value to be returned
  * @param[in]   f2         Float value to be returned
  */
  RTresult RTAPI rtVariableGet2f(RTvariable v, float* f1, float* f2);
  
  /**
  * @param[in]   v          Specifies the program variable whose value is to be returned
  * @param[in]   f1         Float value to be returned
  * @param[in]   f2         Float value to be returned
  * @param[in]   f3         Float value to be returned
  */
  RTresult RTAPI rtVariableGet3f(RTvariable v, float* f1, float* f2, float* f3);
  
  /**
  * @param[in]   v          Specifies the program variable whose value is to be returned
  * @param[in]   f1         Float value to be returned
  * @param[in]   f2         Float value to be returned
  * @param[in]   f3         Float value to be returned
  * @param[in]   f4         Float value to be returned
  */
  RTresult RTAPI rtVariableGet4f(RTvariable v, float* f1, float* f2, float* f3, float* f4);
  
  /**
  * @param[in]   v          Specifies the program variable whose value is to be returned
  * @param[in]   f          Array of float value(s) to be returned
  */
  RTresult RTAPI rtVariableGet1fv(RTvariable v, float* f);
  
  /**
  * @param[in]   v          Specifies the program variable whose value is to be returned
  * @param[in]   f          Array of float value(s) to be returned
  */
  RTresult RTAPI rtVariableGet2fv(RTvariable v, float* f);
  
  /**
  * @param[in]   v          Specifies the program variable whose value is to be returned
  * @param[in]   f          Array of float value(s) to be returned
  */
  RTresult RTAPI rtVariableGet3fv(RTvariable v, float* f);
  
  /**
  * @param[in]   v          Specifies the program variable whose value is to be returned
  * @param[in]   f          Array of float value(s) to be returned
  */
  RTresult RTAPI rtVariableGet4fv(RTvariable v, float* f);

  /**
  * @param[in]   v          Specifies the program variable whose value is to be returned
  * @param[in]   i1         Integer value to be returned
  */
  RTresult RTAPI rtVariableGet1i(RTvariable v, int* i1);
  
  /**
  * @param[in]   v          Specifies the program variable whose value is to be returned
  * @param[in]   i1         Integer value to be returned
  * @param[in]   i2         Integer value to be returned
  */
  RTresult RTAPI rtVariableGet2i(RTvariable v, int* i1, int* i2);
  
  /**
  * @param[in]   v          Specifies the program variable whose value is to be returned
  * @param[in]   i1         Integer value to be returned
  * @param[in]   i2         Integer value to be returned
  * @param[in]   i3         Integer value to be returned
  */
  RTresult RTAPI rtVariableGet3i(RTvariable v, int* i1, int* i2, int* i3);
  
  /**
  * @param[in]   v          Specifies the program variable whose value is to be returned
  * @param[in]   i1         Integer value to be returned
  * @param[in]   i2         Integer value to be returned
  * @param[in]   i3         Integer value to be returned
  * @param[in]   i4         Integer value to be returned
  */
  RTresult RTAPI rtVariableGet4i(RTvariable v, int* i1, int* i2, int* i3, int* i4);
  
  /**
  * @param[in]   v          Specifies the program variable whose value is to be returned
  * @param[in]   i          Array of integer values to be returned
  */
  RTresult RTAPI rtVariableGet1iv(RTvariable v, int* i);
  
  /**
  * @param[in]   v          Specifies the program variable whose value is to be returned
  * @param[in]   i          Array of integer values to be returned
  */
  RTresult RTAPI rtVariableGet2iv(RTvariable v, int* i);
  
  /**
  * @param[in]   v          Specifies the program variable whose value is to be returned
  * @param[in]   i          Array of integer values to be returned
  */
  RTresult RTAPI rtVariableGet3iv(RTvariable v, int* i);
  
  /**
  * @param[in]   v          Specifies the program variable whose value is to be returned
  * @param[in]   i          Array of integer values to be returned
  */
  RTresult RTAPI rtVariableGet4iv(RTvariable v, int* i);

  /**
  * @param[in]   v          Specifies the program variable whose value is to be returned
  * @param[in]   u1         Unsigned integer value to be returned
  */
  RTresult RTAPI rtVariableGet1ui(RTvariable v, unsigned int* u1);
  
  /**
  * @param[in]   v          Specifies the program variable whose value is to be returned
  * @param[in]   u1         Unsigned integer value to be returned
  * @param[in]   u2         Unsigned integer value to be returned
  */
  RTresult RTAPI rtVariableGet2ui(RTvariable v, unsigned int* u1, unsigned int* u2);
  
  /**
  * @param[in]   v          Specifies the program variable whose value is to be returned
  * @param[in]   u1         Unsigned integer value to be returned
  * @param[in]   u2         Unsigned integer value to be returned
  * @param[in]   u3         Unsigned integer value to be returned
  */
  RTresult RTAPI rtVariableGet3ui(RTvariable v, unsigned int* u1, unsigned int* u2, unsigned int* u3);
  
  /**
  * @param[in]   v          Specifies the program variable whose value is to be returned
  * @param[in]   u1         Unsigned integer value to be returned
  * @param[in]   u2         Unsigned integer value to be returned
  * @param[in]   u3         Unsigned integer value to be returned
  * @param[in]   u4         Unsigned integer value to be returned
  */
  RTresult RTAPI rtVariableGet4ui(RTvariable v, unsigned int* u1, unsigned int* u2, unsigned int* u3, unsigned int* u4);
  
  /**
  * @param[in]   v          Specifies the program variable whose value is to be returned
  * @param[in]   u          Array of unsigned integer values to be returned
  */
  RTresult RTAPI rtVariableGet1uiv(RTvariable v, unsigned int* u);
  
  /**
  * @param[in]   v          Specifies the program variable whose value is to be returned
  * @param[in]   u          Array of unsigned integer values to be returned
  */
  RTresult RTAPI rtVariableGet2uiv(RTvariable v, unsigned int* u);
  
  /**
  * @param[in]   v          Specifies the program variable whose value is to be returned
  * @param[in]   u          Array of unsigned integer values to be returned
  */
  RTresult RTAPI rtVariableGet3uiv(RTvariable v, unsigned int* u);
  
  /**
  * @param[in]   v          Specifies the program variable whose value is to be returned
  * @param[in]   u          Array of unsigned integer values to be returned
  */
  RTresult RTAPI rtVariableGet4uiv(RTvariable v, unsigned int* u);

  /**
  * @param[in]   v          Specifies the program variable whose value is to be returned
  * @param[in]   transpose  Specify(ies) row-major or column-major order
  * @param[in]   m          Array of float values to be returned
  */
  RTresult RTAPI rtVariableGetMatrix2x2fv(RTvariable v, int transpose, float* m);
  
  /**
  * @param[in]   v          Specifies the program variable whose value is to be returned
  * @param[in]   transpose  Specify(ies) row-major or column-major order
  * @param[in]   m          Array of float values to be returned
  */
  RTresult RTAPI rtVariableGetMatrix2x3fv(RTvariable v, int transpose, float* m);
  
  /**
  * @param[in]   v          Specifies the program variable whose value is to be returned
  * @param[in]   transpose  Specify(ies) row-major or column-major order
  * @param[in]   m          Array of float values to be returned
  */
  RTresult RTAPI rtVariableGetMatrix2x4fv(RTvariable v, int transpose, float* m);
  
  /**
  * @param[in]   v          Specifies the program variable whose value is to be returned
  * @param[in]   transpose  Specify(ies) row-major or column-major order
  * @param[in]   m          Array of float values to be returned
  */
  RTresult RTAPI rtVariableGetMatrix3x2fv(RTvariable v, int transpose, float* m);
  
  /**
  * @param[in]   v          Specifies the program variable whose value is to be returned
  * @param[in]   transpose  Specify(ies) row-major or column-major order
  * @param[in]   m          Array of float values to be returned
  */
  RTresult RTAPI rtVariableGetMatrix3x3fv(RTvariable v, int transpose, float* m);
  
  /**
  * @param[in]   v          Specifies the program variable whose value is to be returned
  * @param[in]   transpose  Specify(ies) row-major or column-major order
  * @param[in]   m          Array of float values to be returned
  */
  RTresult RTAPI rtVariableGetMatrix3x4fv(RTvariable v, int transpose, float* m);
  
  /**
  * @param[in]   v          Specifies the program variable whose value is to be returned
  * @param[in]   transpose  Specify(ies) row-major or column-major order
  * @param[in]   m          Array of float values to be returned
  */
  RTresult RTAPI rtVariableGetMatrix4x2fv(RTvariable v, int transpose, float* m);
  
  /**
  * @param[in]   v          Specifies the program variable whose value is to be returned
  * @param[in]   transpose  Specify(ies) row-major or column-major order
  * @param[in]   m          Array of float values to be returned
  */
  RTresult RTAPI rtVariableGetMatrix4x3fv(RTvariable v, int transpose, float* m);
  
  /**
  * @param[in]   v          Specifies the program variable whose value is to be returned
  * @param[in]   transpose  Specify(ies) row-major or column-major order
  * @param[in]   m          Array of float values to be returned
  */
  RTresult RTAPI rtVariableGetMatrix4x4fv(RTvariable v, int transpose, float* m);
  /**
  * @}
  */

  /**
  * @brief Returns the value of a OptiX object program variable
  * 
  * @ingroup Variables
  * 
  * <B>Description</B>
  * 
  * @ref rtVariableGetObject queries the value of a program variable whose data type is a
  * OptiX object.  The target variable is specified by \a variable. The value of the
  * program variable is returned in the location pointed to by \a object. The concrete
  * type of the program variable can be queried using @ref rtVariableGetType, and the @ref
  * RTobject handle returned by @ref rtVariableGetObject may safely be cast to an OptiX
  * handle of corresponding type. If \a variable is not a valid variable, this call sets
  * the location pointed to by \a object to \a NULL and returns @ref
  * RT_ERROR_INVALID_VALUE.
  * 
  * @param[in]   v          Specifies the program variable to be queried
  * @param[out]  object     Returns the value of the program variable
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_TYPE_MISMATCH
  * 
  * <B>History</B>
  * 
  * @ref rtVariableGetObject was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtVariableSetObject,
  * @ref rtVariableGetType,
  * @ref rtContextDeclareVariable
  * 
  */
  RTresult RTAPI rtVariableGetObject(RTvariable v, RTobject* object);
  
  /**
  * @brief Defined
  * 
  * @ingroup Variables
  * 
  * <B>Description</B>
  * 
  * @ref rtVariableGetUserData queries the value of a program variable whose data type is
  * user-defined. The variable of interest is specified by \a variable.  The size of the
  * variable's value must match the value given by the parameter \a size.  The value of
  * the program variable is copied to the memory region pointed to by \a ptr. The storage
  * at location \a ptr must be large enough to accomodate all of the program variable's
  * value data. If \a variable is not a valid variable, this call has no effect and
  * returns @ref RT_ERROR_INVALID_VALUE.
  * 
  * @param[in]   v          Specifies the program variable to be queried
  * @param[in]   size       Specifies the size of the program variable, in bytes
  * @param[out]  ptr        The target memory location where to copy the value of the variable
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtVariableGetUserData was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtVariableSetUserData,
  * @ref rtContextDeclareVariable
  * 
  */
  RTresult RTAPI rtVariableGetUserData(RTvariable v, RTsize size, void* ptr);
  

  /* Other */
  /**
  * @brief Queries the name of a program variable
  * 
  * @ingroup Variables
  * 
  * <B>Description</B>
  * 
  * Queries a program variable's name. The variable of interest is specified by \a
  * variable, which should be a value returned by @ref rtContextDeclareVariable. A pointer
  * to the string containing the name of the variable shall be returned to the location
  * pointed to by the pointer \a name_return. If \a variable is not a valid variable, this
  * call sets \a *name_return to \a NULL and returns @ref RT_ERROR_INVALID_VALUE.  \a
  * *name_return will point to valid memory until another API function that returns a
  * string is called.
  * 
  * @param[in]   v             Specifies the program variable to be queried
  * @param[out]  name_return   Returns the program variable's name
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtVariableGetName was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtContextDeclareVariable
  * 
  */
  RTresult RTAPI rtVariableGetName(RTvariable v, const char** name_return);
  
  /**
  * @brief Queries the annotation string of a program variable
  * 
  * @ingroup Variables
  * 
  * <B>Description</B>
  * 
  * @ref rtVariableGetAnnotation queries a program variable's annotation string. A pointer
  * to the string containing the annotation shall be returned to the location pointed to
  * by the pointer \a annotation_return. If \a v is not a valid variable, this call sets
  * \a *annotation_return to \a NULL and returns @ref RT_ERROR_INVALID_VALUE.  \a
  * *annotation_return will point to valid memory until another API function that returns
  * a string is called.
  * 
  * @param[in]   v                   Specifies the program variable to be queried
  * @param[out]  annotation_return   Returns the program variable's annotation string
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtVariableGetAnnotation was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtDeclareVariable,
  * @ref rtDeclareAnnotation
  * 
  */
  RTresult RTAPI rtVariableGetAnnotation(RTvariable v, const char** annotation_return);
  
  /**
  * @brief Returns type information about a program variable
  * 
  * @ingroup Variables
  * 
  * <B>Description</B>
  * 
  * @ref rtVariableGetType queries a program variable's type. The variable of interest is
  * specified by \a variable. The enumeration identifying the type of the program variable
  * shall be returned to the location pointed to by \a type_return, if it is not equal to
  * \a NULL. In this case, after @ref rtVariableGetType, the location pointed to by \a
  * type_return shall be one of the following:
  * 
  *   - @ref RT_OBJECTTYPE_UNKNOWN
  *   - @ref RT_OBJECTTYPE_GROUP
  *   - @ref RT_OBJECTTYPE_GEOMETRY_GROUP
  *   - @ref RT_OBJECTTYPE_TRANSFORM
  *   - @ref RT_OBJECTTYPE_SELECTOR
  *   - @ref RT_OBJECTTYPE_GEOMETRY_INSTANCE
  *   - @ref RT_OBJECTTYPE_BUFFER
  *   - @ref RT_OBJECTTYPE_TEXTURE_SAMPLER
  *   - @ref RT_OBJECTTYPE_OBJECT
  *   - @ref RT_OBJECTTYPE_MATRIX_FLOAT2x2
  *   - @ref RT_OBJECTTYPE_MATRIX_FLOAT2x3
  *   - @ref RT_OBJECTTYPE_MATRIX_FLOAT2x4
  *   - @ref RT_OBJECTTYPE_MATRIX_FLOAT3x2
  *   - @ref RT_OBJECTTYPE_MATRIX_FLOAT3x3
  *   - @ref RT_OBJECTTYPE_MATRIX_FLOAT3x4
  *   - @ref RT_OBJECTTYPE_MATRIX_FLOAT4x2
  *   - @ref RT_OBJECTTYPE_MATRIX_FLOAT4x3
  *   - @ref RT_OBJECTTYPE_MATRIX_FLOAT4x4
  *   - @ref RT_OBJECTTYPE_FLOAT
  *   - @ref RT_OBJECTTYPE_FLOAT2
  *   - @ref RT_OBJECTTYPE_FLOAT3
  *   - @ref RT_OBJECTTYPE_FLOAT4
  *   - @ref RT_OBJECTTYPE_INT
  *   - @ref RT_OBJECTTYPE_INT2
  *   - @ref RT_OBJECTTYPE_INT3
  *   - @ref RT_OBJECTTYPE_INT4
  *   - @ref RT_OBJECTTYPE_UNSIGNED_INT
  *   - @ref RT_OBJECTTYPE_UNSIGNED_INT2
  *   - @ref RT_OBJECTTYPE_UNSIGNED_INT3
  *   - @ref RT_OBJECTTYPE_UNSIGNED_INT4
  *   - @ref RT_OBJECTTYPE_USER
  * 
  * If \a variable is not valid, this call returns @ref RT_ERROR_INVALID_VALUE.
  * 
  * @param[in]   v             Specifies the program variable to be queried
  * @param[out]  type_return   Returns the type of the program variable
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtVariableGetType was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtContextDeclareVariable
  * 
  */
  RTresult RTAPI rtVariableGetType(RTvariable v, RTobjecttype* type_return);
  
  /**
  * @brief Returns the context associated with a program variable
  * 
  * @ingroup Variables
  * 
  * <B>Description</B>
  * 
  * @ref rtVariableGetContext queries the context associated with a program variable.  The
  * target variable is specified by \a variable. The context of the program variable is
  * returned to \a *context if the pointer \a context is not \a NULL. If \a variable is
  * not a valid variable, \a *context is set to \a NULL and @ref RT_ERROR_INVALID_VALUE is
  * returned.
  * 
  * @param[in]   v          Specifies the program variable to be queried
  * @param[out]  context    Returns the context associated with the program variable
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtVariableGetContext was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtContextDeclareVariable
  * 
  */
  RTresult RTAPI rtVariableGetContext(RTvariable v, RTcontext* context);
  
  /**
  * @brief Queries the size, in bytes, of a variable
  * 
  * @ingroup Variables
  * 
  * <B>Description</B>
  * 
  * @ref rtVariableGetSize queries a declared program variable for its size in bytes.
  * This is most often used to query the size of a variable that has a user-defined type.
  * Builtin types (int, float, unsigned int, etc.) may be queried, but object typed
  * variables, such as buffers, texture samplers and graph nodes, cannot be queried and
  * will return @ref RT_ERROR_INVALID_VALUE.
  * 
  * @param[in]   v          Specifies the program variable to be queried
  * @param[out]  size       Specifies a pointer where the size of the variable, in bytes, will be returned
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtVariableGetSize was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtVariableGetUserData,
  * @ref rtContextDeclareVariable
  * 
  */
  RTresult RTAPI rtVariableGetSize(RTvariable v, RTsize* size);
  

/************************************
 **
 **    Context object
 **
 ***********************************/

  /**
  * @brief Creates a new context object
  * 
  * @ingroup Context
  * 
  * <B>Description</B>
  * 
  * @ref rtContextCreate allocates and returns a handle to a new context object.
  * Returns @ref RT_ERROR_INVALID_VALUE if passed a \a NULL pointer.
  * 
  * @param[out]  context   Handle to context for return value
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_NO_DEVICE
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtContextCreate was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * 
  * 
  */
  RTresult RTAPI rtContextCreate(RTcontext* context);
  
  /**
  * @brief Destroys a context and frees all associated resources
  * 
  * @ingroup Context
  * 
  * <B>Description</B>
  * 
  * @ref rtContextDestroy frees all resources, including OptiX objects, associated with
  * this object.  Returns @ref RT_ERROR_INVALID_VALUE if passed a \a NULL context.  @ref
  * RT_ERROR_LAUNCH_FAILED may be returned if a previous call to @ref rtContextLaunch "rtContextLaunch"
  * failed.
  * 
  * @param[in]   context   Handle of the context to destroy
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_LAUNCH_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtContextDestroy was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtContextCreate
  * 
  */
  RTresult RTAPI rtContextDestroy(RTcontext  context);
  
  /**
  * @brief Checks the given context for valid internal state
  * 
  * @ingroup Context
  * 
  * <B>Description</B>
  * 
  * @ref rtContextValidate checks the the given context and all of its associated OptiX
  * objects for a valid state.  These checks include tests for presence of necessary
  * programs (eg. an intersection program for a geometry node), invalid internal state
  * such as \a NULL children in graph nodes, and presence of variables required by all
  * specified programs. @ref rtContextGetErrorString can be used to retrieve a description
  * of a validation failure.
  * 
  * @param[in]   context   The context to be validated
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_INVALID_SOURCE
  * 
  * <B>History</B>
  * 
  * @ref rtContextValidate was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtContextGetErrorString
  * 
  */
  RTresult RTAPI rtContextValidate(RTcontext  context);

  /**
  * @brief Returns the error string associated with a given
  * error
  * 
  * @ingroup Context
  * 
  * <B>Description</B>
  * 
  * @ref rtContextGetErrorString return a descriptive string given an error code.  If \a
  * context is valid and additional information is available from the last OptiX failure,
  * it will be appended to the generic error code description.  \a return_string will be
  * set to point to this string.  The memory \a return_string points to will be valid
  * until the next API call that returns a string.
  * 
  * @param[in]   context         The context object to be queried, or \a NULL
  * @param[in]   code            The error code to be converted to string
  * @param[out]  return_string   The return parameter for the error string
  * 
  * <B>Return values</B>
  *
  * @ref rtContextGetErrorString does not return a value
  * 
  * <B>History</B>
  * 
  * @ref rtContextGetErrorString was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * 
  * 
  */
  void RTAPI rtContextGetErrorString(RTcontext context, RTresult code, const char** return_string);

  /**
  * @brief Set an attribute specific to an OptiX context
  * 
  * @ingroup Context
  * 
  * <B>Description</B>
  * 
  * @ref rtContextSetAttribute sets \a p as the value of the per context attribute
  * specified by \a attrib.
  * 
  * Each attribute can have a different size.  The sizes are given in the following list:
  * 
  *   - @ref RT_CONTEXT_ATTRIBUTE_CPU_NUM_THREADS          sizeof(int)
  *   - @ref RT_CONTEXT_ATTRIBUTE_GPU_PAGING_FORCED_OFF    sizeof(int)
  * 
  * @ref RT_CONTEXT_ATTRIBUTE_CPU_NUM_THREADS sets the number of host CPU threads OptiX
  * can use for various tasks.
  * 
  * @ref RT_CONTEXT_ATTRIBUTE_GPU_PAGING_FORCED_OFF prohibits software paging of device
  * memory. A value of 0 means that OptiX is allowed to activate paging if necessary, 1
  * means that paging is always off. Note that currently paging cannot be disabled once it
  * has been activated.
  * 
  * @param[in]   context   The context object to be modified
  * @param[in]   attrib    Attribute to set
  * @param[in]   size      Size of the attribute being set
  * @param[in]   p         Pointer to where the value of the attribute will be copied from.  This must point to at least \a size bytes of memory
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE - Can be returned if \a size does not match the proper size of the attribute, or if \a p
  * is \a NULL
  * 
  * <B>History</B>
  * 
  * @ref rtContextSetAttribute was introduced in OptiX 2.5.
  * 
  * <B>See also</B>
  * @ref rtContextGetAttribute
  * 
  */
  RTresult RTAPI rtContextSetAttribute(RTcontext context, RTcontextattribute attrib, RTsize size, void* p);
  
  /**
  * @brief Returns an attribute specific to an OptiX context
  * 
  * @ingroup Context
  * 
  * <B>Description</B>
  * 
  * @ref rtContextGetAttribute returns in \a p the value of the per context attribute
  * specified by \a attrib.
  * 
  * Each attribute can have a different size.  The sizes are given in the following list:
  * 
  *   - @ref RT_CONTEXT_ATTRIBUTE_MAX_TEXTURE_COUNT        sizeof(int)
  *   - @ref RT_CONTEXT_ATTRIBUTE_CPU_NUM_THREADS          sizeof(int)
  *   - @ref RT_CONTEXT_ATTRIBUTE_USED_HOST_MEMORY         sizeof(RTsize)
  *   - @ref RT_CONTEXT_ATTRIBUTE_GPU_PAGING_ACTIVE        sizeof(int)
  *   - @ref RT_CONTEXT_ATTRIBUTE_GPU_PAGING_FORCED_OFF    sizeof(int)
  *   - @ref RT_CONTEXT_ATTRIBUTE_AVAILABLE_DEVICE_MEMORY  sizeof(RTsize)
  * 
  * @ref RT_CONTEXT_ATTRIBUTE_MAX_TEXTURE_COUNT queries the maximum number of textures
  * handled by OptiX. For OptiX versions below 2.5 this value depends on the number of
  * textures supported by CUDA.
  * 
  * @ref RT_CONTEXT_ATTRIBUTE_CPU_NUM_THREADS queries the number of host CPU threads OptiX
  * can use for various tasks.
  * 
  * @ref RT_CONTEXT_ATTRIBUTE_USED_HOST_MEMORY queries the amount of host memory allocated
  * by OptiX.
  * 
  * @ref RT_CONTEXT_ATTRIBUTE_GPU_PAGING_ACTIVE queries if software paging of device
  * memory has been turned on by the context. The returned value is a boolean, where 1
  * means that paging is currently active.
  * 
  * @ref RT_CONTEXT_ATTRIBUTE_GPU_PAGING_FORCED_OFF queries if software paging has been
  * prohibited by the user. The returned value is a boolean, where 0 means that OptiX is
  * allowed to activate paging if necessary, 1 means that paging is always off.
  * 
  * @ref RT_CONTEXT_ATTRIBUTE_AVAILABLE_DEVICE_MEMORY queries the amount of free device
  * memory.
  * 
  * Some attributes are used to get per device information.  In constrast to @ref
  * rtDeviceGetAttribute, these attributes are determined by the context and are therefore
  * queried through the context.  This is done by summing the attribute with the OptiX
  * ordinal number when querying the attribute.  The following are per device attributes.
  * 
  *   @ref RT_CONTEXT_ATTRIBUTE_AVAILABLE_DEVICE_MEMORY
  * 
  * @param[in]   context   The context object to be queried
  * @param[in]   attrib    Attribute to query
  * @param[in]   size      Size of the attribute being queried.  Parameter \a p must have at least this much memory backing it
  * @param[out]  p         Return pointer where the value of the attribute will be copied into.  This must point to at least \a size bytes of memory
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE - Can be returned if \a size does not match the proper size of the attribute, if \a p is
  * \a NULL, or if \a attribute+ordinal does not correspond to an OptiX device
  * 
  * <B>History</B>
  * 
  * @ref rtContextGetAttribute was introduced in OptiX 2.0.
  * 
  * <B>See also</B>
  * @ref rtContextGetDeviceCount,
  * @ref rtContextSetAttribute,
  * @ref rtDeviceGetAttribute
  * 
  */
  RTresult RTAPI rtContextGetAttribute(RTcontext context, RTcontextattribute attrib, RTsize size, void* p);

  /**
  * @brief Specify a list of hardware devices to be used by the
  * kernel
  * 
  * @ingroup Context
  * 
  * <B>Description</B>
  * 
  * @ref rtContextSetDevices specifies a list of hardware devices to be used during
  * execution of the subsequent trace kernels.
  * 
  * @param[in]   context   The context to which the hardware list is applied
  * @param[in]   count     The number of devices in the list
  * @param[in]   devices   The list of devices
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_NO_DEVICE
  * - @ref RT_ERROR_INVALID_DEVICE
  * 
  * <B>History</B>
  * 
  * @ref rtContextSetDevices was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtContextGetDevices,
  * @ref rtContextGetDeviceCount
  * 
  */
  RTresult RTAPI rtContextSetDevices(RTcontext context, unsigned int count, const int* devices);
  
  /**
  * @brief Retrieve a list of hardware devices being used by the
  * kernel
  * 
  * @ingroup Context
  * 
  * <B>Description</B>
  * 
  * @ref rtContextGetDevices retrieves a list of hardware devices used during execution
  * of the subsequent trace kernels.
  * 
  * @param[in]   context   The context to which the hardware list is applied
  * @param[out]  devices   Return parameter for the list of devices.  The memory must be able to hold entries
  * numbering least the number of devices as returned by @ref rtContextGetDeviceCount
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtContextGetDevices was introduced in OptiX 2.0.
  * 
  * <B>See also</B>
  * @ref rtContextSetDevices,
  * @ref rtContextGetDeviceCount
  * 
  */
  RTresult RTAPI rtContextGetDevices(RTcontext context, int* devices);
  
  /**
  * @brief Query the number of devices currently being used
  * 
  * @ingroup Context
  * 
  * <B>Description</B>
  * 
  * @ref rtContextGetDeviceCount - Query the number of devices currently being used.
  * 
  * @param[in]   context   The context containing the devices
  * @param[out]  count     Return parameter for the device count
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtContextGetDeviceCount was introduced in OptiX 2.0.
  * 
  * <B>See also</B>
  * @ref rtContextSetDevices,
  * @ref rtContextGetDevices
  * 
  */
  RTresult RTAPI rtContextGetDeviceCount(RTcontext context, unsigned int* count);

  /**
  * @brief Set the stack size for a given context
  * 
  * @ingroup Context
  * 
  * <B>Description</B>
  * 
  * @ref rtContextSetStackSize sets the stack size for the given context to
  * \a stack_size_bytes bytes. Returns @ref RT_ERROR_INVALID_VALUE if context is not valid.
  * 
  * @param[in]   context            The context node to be modified
  * @param[in]   stack_size_bytes   The desired stack size in bytes
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtContextSetStackSize was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtContextGetStackSize
  * 
  */
  RTresult RTAPI rtContextSetStackSize(RTcontext context, RTsize  stack_size_bytes);
  
  /**
  * @brief Query the stack size for this context
  * 
  * @ingroup Context
  * 
  * <B>Description</B>
  * 
  * @ref rtContextGetStackSize passes back the stack size associated with this context in
  * \a stack_size_bytes.  Returns @ref RT_ERROR_INVALID_VALUE if passed a \a NULL pointer.
  * 
  * @param[in]   context            The context node to be queried
  * @param[out]  stack_size_bytes   Return parameter to store the size of the stack
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtContextGetStackSize was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtContextSetStackSize
  * 
  */
  RTresult RTAPI rtContextGetStackSize(RTcontext context, RTsize* stack_size_bytes);
  

  /**
  * @brief Side timeout callback function
  * 
  * @ingroup Context
  * 
  * <B>Description</B>
  * 
  * @ref rtContextSetTimeoutCallback sets an application-side callback function
  * \a callback and a time interval \a min_polling_seconds in
  * seconds. Long-running OptiX API calls such as @ref rtContextCompile
  * and @ref rtContextLaunch "rtContextLaunch" call the callback function about every
  * \a min_polling_seconds seconds. If the callback function returns true,
  * the API call tries to abort, leaving the context in a clean but
  * unfinished state. Output buffers are left in an unpredictable state.
  * In case an OptiX API call is terminated by a callback function, it
  * returns @ref RT_TIMEOUT_CALLBACK.
  * 
  * @ref RTtimeoutcallback is defined as \a int (*RTtimeoutcallback)(void).
  * 
  * To unregister a callback function, \a callback needs to be set to
  * \a NULL and \a min_polling_seconds to 0.
  * 
  * Returns @ref RT_ERROR_INVALID_VALUE if \a context is not valid, if
  * \a min_polling_seconds is negative, if \a callback is \a NULL but
  * \a min_polling_seconds is not 0, or if \a callback is not \a NULL but
  * \a min_polling_seconds is 0.
  * 
  * @param[in]   context               The context node to be modified
  * @param[in]   callback              The function to be called
  * @param[in]   min_polling_seconds   The timeout interval after which the function is called
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtContextSetTimeoutCallback was introduced in OptiX 2.5.
  * 
  * <B>See also</B>
  * @ref rtContextCompile,
  * @ref rtContextLaunch
  * 
  */
  RTresult RTAPI rtContextSetTimeoutCallback(RTcontext context, RTtimeoutcallback callback, double min_polling_seconds);

  /**
  * @brief Set the number of entry points for a given context
  * 
  * @ingroup Context
  * 
  * <B>Description</B>
  * 
  * @ref rtContextSetEntryPointCount sets the number of entry points associated with
  * the given context to \a num_entry_points.
  * 
  * @param[in]   context            The context to be modified
  * @param[in]   num_entry_points   The number of entry points to use
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtContextSetEntryPointCount was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtContextGetEntryPointCount
  * 
  */
  RTresult RTAPI rtContextSetEntryPointCount(RTcontext context, unsigned int  num_entry_points);
  
  /**
  * @brief Query the number of entry points for this
  * context
  * 
  * @ingroup Context
  * 
  * <B>Description</B>
  * 
  * @ref rtContextGetEntryPointCount passes back the number of entry points associated
  * with this context in \a num_entry_points.  Returns @ref RT_ERROR_INVALID_VALUE if
  * passed a \a NULL pointer.
  * 
  * @param[in]   context            The context node to be queried
  * @param[out]  num_entry_points   Return parameter for passing back the entry point count
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtContextGetEntryPointCount was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtContextSetEntryPointCount
  * 
  */
  RTresult RTAPI rtContextGetEntryPointCount(RTcontext context, unsigned int* num_entry_points);

  /**
  * @brief Specifies the ray generation program for
  * a given context entry point
  * 
  * @ingroup Context
  * 
  * <B>Description</B>
  * 
  * @ref rtContextSetRayGenerationProgram sets \a context's ray generation program at
  * entry point \a entry_point_index. @ref RT_ERROR_INVALID_VALUE is returned if \a
  * entry_point_index is outside of the range [\a 0, @ref rtContextGetEntryPointCount
  * \a -1].
  * 
  * @param[in]   context             The context node to which the exception program will be added
  * @param[in]   entry_point_index   The entry point the program will be associated with
  * @param[in]   program             The ray generation program
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * - @ref RT_ERROR_TYPE_MISMATCH
  * 
  * <B>History</B>
  * 
  * @ref rtContextSetRayGenerationProgram was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtContextGetEntryPointCount,
  * @ref rtContextGetRayGenerationProgram
  * 
  */
  RTresult RTAPI rtContextSetRayGenerationProgram(RTcontext context, unsigned int entry_point_index, RTprogram  program);
  
  /**
  * @brief Queries the ray generation program
  * associated with the given context and entry point
  * 
  * @ingroup Context
  * 
  * <B>Description</B>
  * 
  * @ref rtContextGetRayGenerationProgram passes back the ray generation program
  * associated with the given context and entry point.  This program is set via @ref
  * rtContextSetRayGenerationProgram.  Returns @ref RT_ERROR_INVALID_VALUE if given an
  * invalid entry point index or \a NULL pointer.
  * 
  * @param[in]   context             The context node associated with the ray generation program
  * @param[in]   entry_point_index   The entry point index for the desired ray generation program
  * @param[out]  program             Return parameter to store the ray generation program
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtContextGetRayGenerationProgram was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtContextSetRayGenerationProgram
  * 
  */
  RTresult RTAPI rtContextGetRayGenerationProgram(RTcontext context, unsigned int entry_point_index, RTprogram* program);

  /**
  * @brief Specifies the exception program for a given context entry point
  * 
  * @ingroup Context
  * 
  * <B>Description</B>
  * 
  * @ref rtContextSetExceptionProgram sets \a context's exception program at entry point
  * \a entry_point_index. @ref RT_ERROR_INVALID_VALUE is returned if \a entry_point_index
  * is outside of the range [\a 0, @ref rtContextGetEntryPointCount \a -1].
  * 
  * @param[in]   context             The context node to which the exception program will be added
  * @param[in]   entry_point_index   The entry point the program will be associated with
  * @param[in]   program             The exception program
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_TYPE_MISMATCH
  * 
  * <B>History</B>
  * 
  * @ref rtContextSetExceptionProgram was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtContextGetEntryPointCount,
  * @ref rtContextGetExceptionProgram
  * @ref rtContextSetExceptionEnabled,
  * @ref rtContextGetExceptionEnabled,
  * @ref rtGetExceptionCode,
  * @ref rtThrow,
  * @ref rtPrintExceptionDetails
  * 
  */
  RTresult RTAPI rtContextSetExceptionProgram(RTcontext context, unsigned int entry_point_index, RTprogram  program);
  
  /**
  * @brief Queries the exception program associated with
  * the given context and entry point
  * 
  * @ingroup Context
  * 
  * <B>Description</B>
  * 
  * @ref rtContextGetExceptionProgram passes back the exception program associated with
  * the given context and entry point.  This program is set via @ref
  * rtContextSetExceptionProgram.  Returns @ref RT_ERROR_INVALID_VALUE if given an invalid
  * entry point index or \a NULL pointer.
  * 
  * @param[in]   context             The context node associated with the exception program
  * @param[in]   entry_point_index   The entry point index for the desired exception program
  * @param[out]  program             Return parameter to store the exception program
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtContextGetExceptionProgram was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtContextSetExceptionProgram,
  * @ref rtContextSetEntryPointCount,
  * @ref rtContextSetExceptionEnabled,
  * @ref rtContextGetExceptionEnabled,
  * @ref rtGetExceptionCode,
  * @ref rtThrow,
  * @ref rtPrintExceptionDetails
  * 
  */
  RTresult RTAPI rtContextGetExceptionProgram(RTcontext context, unsigned int entry_point_index, RTprogram* program);

  /**
  * @brief Enable or disable an exception
  * 
  * @ingroup Context
  * 
  * <B>Description</B>
  * 
  * @ref rtContextSetExceptionEnabled is used to enable or disable specific exceptions.
  * If an exception is enabled, the exception condition is checked for at runtime, and the
  * exception program is invoked if the condition is met. The exception program can query
  * the type of the caught exception by calling @ref rtGetExceptionCode.
  * \a exception may take one of the following values:
  * 
  *   - @ref RT_EXCEPTION_TEXTURE_ID_INVALID
  *   - @ref RT_EXCEPTION_BUFFER_ID_INVALID
  *   - @ref RT_EXCEPTION_INDEX_OUT_OF_BOUNDS
  *   - @ref RT_EXCEPTION_STACK_OVERFLOW
  *   - @ref RT_EXCEPTION_BUFFER_INDEX_OUT_OF_BOUNDS
  *   - @ref RT_EXCEPTION_INVALID_RAY
  *   - @ref RT_EXCEPTION_INTERNAL_ERROR
  *   - @ref RT_EXCEPTION_USER
  *   - @ref RT_EXCEPTION_ALL
  *   
  * 
  * @ref RT_EXCEPTION_TEXTURE_ID_INVALID verifies that every access of a texture id is
  * valid, including use of RT_TEXTURE_ID_NULL and IDs out of bounds.
  * 
  * @ref RT_EXCEPTION_BUFFER_ID_INVALID verifies that every access of a buffer id is
  * valid, including use of RT_BUFFER_ID_NULL and IDs out of bounds.
  *
  * @ref RT_EXCEPTION_INDEX_OUT_OF_BOUNDS checks that @ref rtIntersectChild and @ref
  * rtReportIntersection are called with a valid index.
  * 
  * @ref RT_EXCEPTION_STACK_OVERFLOW checks the runtime stack against overflow. The most
  * common cause for an overflow is a too deep @ref rtTrace recursion tree.
  * 
  * @ref RT_EXCEPTION_BUFFER_INDEX_OUT_OF_BOUNDS checks every read and write access to
  * @ref rtBuffer objects to be within valid bounds.
  * 
  * @ref RT_EXCEPTION_INVALID_RAY checks the each ray's origin and direction values
  * against \a NaNs and \a infinity values.
  * 
  * @ref RT_EXCEPTION_INTERNAL_ERROR indicates an unexpected internal error in the
  * runtime.
  * 
  * @ref RT_EXCEPTION_USER is used to enable or disable all user-defined exceptions. The
  * reserved range of exception codes for user-defined exceptions starts at @ref
  * RT_EXCEPTION_USER (\a 0x400) and ends at \a 0xFFFF. See @ref rtThrow for more
  * information.
  * 
  * @ref RT_EXCEPTION_ALL is a placeholder value which can be used to enable or disable
  * all possible exceptions with a single call to @ref rtContextSetExceptionEnabled.
  * 
  * By default, @ref RT_EXCEPTION_STACK_OVERFLOW is enabled and all other exceptions are
  * disabled.
  * 
  * @param[in]   context     The context for which the exception is to be enabled or disabled
  * @param[in]   exception   The exception which is to be enabled or disabled
  * @param[in]   enabled     Nonzero to enable the exception, \a 0 to disable the exception
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtContextSetExceptionEnabled was introduced in OptiX 1.1.
  * 
  * <B>See also</B>
  * @ref rtContextGetExceptionEnabled,
  * @ref rtContextSetExceptionProgram,
  * @ref rtContextGetExceptionProgram,
  * @ref rtGetExceptionCode,
  * @ref rtThrow,
  * @ref rtPrintExceptionDetails
  * 
  */
  RTresult RTAPI rtContextSetExceptionEnabled(RTcontext context, RTexception exception, int  enabled );
  
  /**
  * @brief Query whether a specified exception is enabled
  * 
  * @ingroup Context
  * 
  * <B>Description</B>
  * 
  * @ref rtContextGetExceptionEnabled passes back \a 1 in the location pointed
  * to by \a enabled if the given exception is enabled, \a 0 otherwise.
  * \a exception specifies the type of exception to be queried. For a list
  * of available types, see @ref rtContextSetExceptionEnabled. If \a exception
  * is @ref RT_EXCEPTION_ALL, \a enabled is set to \a 1 only if all possible
  * exceptions are enabled.
  * 
  * @param[in]   context     The context to be queried
  * @param[in]   exception   The exception of which to query the state
  * @param[out]  enabled     Return parameter to store whether the exception is enabled
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtContextGetExceptionEnabled was introduced in OptiX 1.1.
  * 
  * <B>See also</B>
  * @ref rtContextSetExceptionEnabled,
  * @ref rtContextSetExceptionProgram,
  * @ref rtContextGetExceptionProgram,
  * @ref rtGetExceptionCode,
  * @ref rtThrow,
  * @ref rtPrintExceptionDetails
  * 
  */
  RTresult RTAPI rtContextGetExceptionEnabled(RTcontext context, RTexception exception, int* enabled );

  /**
  * @brief Sets the number of ray types for a given context
  * 
  * @ingroup Context
  * 
  * <B>Description</B>
  * 
  * @ref rtContextSetRayTypeCount Sets the number of ray types associated with the given
  * context.
  * 
  * @param[in]   context         The context node
  * @param[in]   num_ray_types   The number of ray types to be used
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtContextSetRayTypeCount was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtContextGetRayTypeCount
  * 
  */
  RTresult RTAPI rtContextSetRayTypeCount(RTcontext context, unsigned int  num_ray_types);
  
  /**
  * @brief Query the number of ray types associated with this
  * context
  * 
  * @ingroup Context
  * 
  * <B>Description</B>
  * 
  * @ref rtContextGetRayTypeCount passes back the number of entry points associated with
  * this context in \a num_ray_types.  Returns @ref RT_ERROR_INVALID_VALUE if passed a \a
  * NULL pointer.
  * 
  * @param[in]   context         The context node to be queried
  * @param[out]  num_ray_types   Return parameter to store the number of ray types
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtContextGetRayTypeCount was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtContextSetRayTypeCount
  * 
  */
  RTresult RTAPI rtContextGetRayTypeCount(RTcontext context, unsigned int* num_ray_types);

  /**
  * @brief Specifies the miss program for a given context ray type
  * 
  * @ingroup Context
  * 
  * <B>Description</B>
  * 
  * @ref rtContextSetMissProgram sets \a context's miss program associated with ray type 
  * \a ray_type_index. @ref RT_ERROR_INVALID_VALUE is returned if \a ray_type_index
  * is outside of the range [\a 0, @ref rtContextGetRayTypeCount \a -1].
  * 
  * @param[in]   context          The context node to which the miss program will be added
  * @param[in]   ray_type_index   The ray type the program will be associated with
  * @param[in]   program          The miss program
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * - @ref RT_ERROR_TYPE_MISMATCH
  * 
  * <B>History</B>
  * 
  * @ref rtContextSetMissProgram was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtContextGetRayTypeCount,
  * @ref rtContextGetMissProgram
  * 
  */
  RTresult RTAPI rtContextSetMissProgram(RTcontext context, unsigned int ray_type_index, RTprogram  program);
  
  /**
  * @brief Queries the miss program associated with the given
  * context and ray type
  * 
  * @ingroup Context
  * 
  * <B>Description</B>
  * 
  * @ref rtContextGetMissProgram passes back the miss program associated with the
  * given context and ray type.  This program is set via @ref rtContextSetMissProgram.
  * Returns @ref RT_ERROR_INVALID_VALUE if given a \a NULL pointer or \a ray_type_index is
  * outside of the range [\a 0, @ref rtContextGetRayTypeCount \a -1].
  * 
  * @param[in]   context          The context node associated with the miss program
  * @param[in]   ray_type_index   The ray type index for the desired miss program
  * @param[out]  program          Return parameter to store the miss program
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtContextGetMissProgram was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtContextSetMissProgram,
  * @ref rtContextGetRayTypeCount
  * 
  */
  RTresult RTAPI rtContextGetMissProgram(RTcontext context, unsigned int ray_type_index, RTprogram* program);

  /**
  * @brief Gets an RTtexturesampler corresponding to the texture id
  * 
  * @ingroup Context
  * 
  * <B>Description</B>
  * 
  * @ref rtTextureSamplerGetId returns a handle to the texture sampler in \a *sampler
  * corresponding to the \a sampler_id supplied.  If \a sampler_id does not map to a valid
  * texture handle, \a *sampler is \a NULL or if \a context is invalid, the call will
  * return @ref RT_ERROR_INVALID_VALUE.
  * 
  * @param[in]   context     The context the sampler should be originated from
  * @param[in]   sampler_id  The ID of the sampler to query
  * @param[out]  sampler     The return handle for the sampler object corresponding to the sampler_id
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtContextGetTextureSamplerFromId was introduced in OptiX 3.5.
  * 
  * <B>See also</B>
  * @ref rtTextureSamplerGetId
  * 
  */
  RTresult RTAPI rtContextGetTextureSamplerFromId(RTcontext context, int sampler_id, RTtexturesampler* sampler);

  /**
  * @brief Compiles a context object
  * 
  * @ingroup Context
  * 
  * <B>Description</B>
  * 
  * @ref rtContextCompile creates a final computation kernel from the given context's
  * programs and scene hierarchy. This kernel will be executed upon subsequent invocations
  * of @ref rtContextLaunch "rtContextLaunch".
  * 
  * Calling @ref rtContextCompile is not strictly necessary since any changes to the scene
  * specification or programs will cause an internal compilation upon the next @ref
  * rtContextLaunch call. @ref rtContextCompile allows the application to control when the
  * compilation work occurs.
  * 
  * Conversely, if no changes to the scene specification or programs have occurred since
  * the last compilation, @ref rtContextCompile and @ref rtContextLaunch "rtContextLaunch" will not perform
  * a recompilation.
  * 
  * @param[in]   context   The context to be compiled
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * - @ref RT_ERROR_INVALID_SOURCE
  * 
  * <B>History</B>
  * 
  * @ref rtContextCompile was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtContextLaunch
  * 
  */
  RTresult RTAPI rtContextCompile(RTcontext context);

  /**
  * @brief Executes the computation kernel for a given context
  * 
  * @ingroup rtContextLaunch
  * 
  * <B>Description</B>
  * 
  * @ref rtContextLaunch "rtContextLaunch" functions execute the computation kernel associated with the
  * given context.  If the context has not yet been compiled, or if the context has been
  * modified since the last compile, @ref rtContextLaunch "rtContextLaunch" will recompile the kernel
  * internally.  Acceleration structures of the context which are marked dirty will be
  * updated and their dirty flags will be cleared.  Similarly, validation will occur if
  * necessary.  The ray generation program specified by \a entry_point_index will be
  * invoked once for every element (pixel or voxel) of the computation grid specified by
  * \a image_width, \a image_height, and \a image_depth.
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * - @ref RT_ERROR_INVALID_SOURCE
  * - @ref RT_ERROR_LAUNCH_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtContextLaunch "rtContextLaunch" was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtContextGetRunningState,
  * @ref rtContextCompile,
  * @ref rtContextValidate
  * 
  */
  /**
  * @ingroup rtContextLaunch
  * @param[in]   context                                    The context to be executed
  * @param[in]   entry_point_index                          The initial entry point into kernel
  * @param[in]   image_width                                Width of the computation grid
  */
  RTresult RTAPI rtContextLaunch1D(RTcontext context, unsigned int entry_point_index, RTsize image_width);
  /**
  * @ingroup rtContextLaunch
  * @param[in]   context                                    The context to be executed
  * @param[in]   entry_point_index                          The initial entry point into kernel
  * @param[in]   image_width                                Width of the computation grid
  * @param[in]   image_height                               Height of the computation grid
  */
  RTresult RTAPI rtContextLaunch2D(RTcontext context, unsigned int entry_point_index, RTsize image_width, RTsize image_height);
  /**
  * @ingroup rtContextLaunch
  * @param[in]   context                                    The context to be executed
  * @param[in]   entry_point_index                          The initial entry point into kernel
  * @param[in]   image_width                                Width of the computation grid
  * @param[in]   image_height                               Height of the computation grid
  * @param[in]   image_depth                                Depth of the computation grid
  */
  RTresult RTAPI rtContextLaunch3D(RTcontext context, unsigned int entry_point_index, RTsize image_width, RTsize image_height, RTsize image_depth);

  /**
  * @brief Query whether the given context is currently
  * running
  * 
  * @ingroup Context
  * 
  * <B>Description</B>
  * 
  * This function is currently unimplemented and it is provided as a placeholder for a future implementation.
  * 
  * @param[in]   context   The context node to be queried
  * @param[out]  running   Return parameter to store the running state
  * 
  * <B>Return values</B>
  * 
  * Since unimplemented, this function will always throw an assertion failure.
  * 
  * <B>History</B>
  * 
  * @ref rtContextGetRunningState was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtContextLaunch1D,
  * @ref rtContextLaunch2D,
  * @ref rtContextLaunch3D
  * 
  */
  RTresult RTAPI rtContextGetRunningState(RTcontext context, int* running);

  /**
  * @brief Enable or disable text printing from programs
  * 
  * @ingroup Context
  * 
  * <B>Description</B>
  * 
  * @ref rtContextSetPrintEnabled is used to control whether text printing in programs
  * through @ref rtPrintf is currently enabled for this context.
  * 
  * @param[in]   context   The context for which printing is to be enabled or disabled
  * @param[in]   enabled   Setting this parameter to a nonzero value enables printing, \a 0 disables printing
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtContextSetPrintEnabled was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtPrintf,
  * @ref rtContextGetPrintEnabled,
  * @ref rtContextSetPrintBufferSize,
  * @ref rtContextGetPrintBufferSize,
  * @ref rtContextSetPrintLaunchIndex,
  * @ref rtContextGetPrintLaunchIndex
  * 
  */
  RTresult RTAPI rtContextSetPrintEnabled(RTcontext context, int  enabled);
  
  /**
  * @brief Query whether text printing from programs
  * is enabled
  * 
  * @ingroup Context
  * 
  * <B>Description</B>
  * 
  * @ref rtContextGetPrintEnabled passes back \a 1 if text printing from programs through
  * @ref rtPrintf is currently enabled for this context; \a 0 otherwise.  Returns @ref
  * RT_ERROR_INVALID_VALUE if passed a \a NULL pointer.
  * 
  * @param[in]   context   The context to be queried
  * @param[out]  enabled   Return parameter to store whether printing is enabled
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtContextGetPrintEnabled was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtPrintf,
  * @ref rtContextSetPrintEnabled,
  * @ref rtContextSetPrintBufferSize,
  * @ref rtContextGetPrintBufferSize,
  * @ref rtContextSetPrintLaunchIndex,
  * @ref rtContextGetPrintLaunchIndex
  * 
  */
  RTresult RTAPI rtContextGetPrintEnabled(RTcontext context, int* enabled);
  
  /**
  * @brief Set the size of the print buffer
  * 
  * @ingroup Context
  * 
  * <B>Description</B>
  * 
  * @ref rtContextSetPrintBufferSize is used to set the buffer size available to hold
  * data generated by @ref rtPrintf. The default size is 65536 bytes.
  * 
  * @param[in]   context             The context for which to set the print buffer size
  * @param[in]   buffer_size_bytes   The print buffer size in bytes
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtContextSetPrintBufferSize was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtPrintf,
  * @ref rtContextSetPrintEnabled,
  * @ref rtContextGetPrintEnabled,
  * @ref rtContextGetPrintBufferSize,
  * @ref rtContextSetPrintLaunchIndex,
  * @ref rtContextGetPrintLaunchIndex
  * 
  */
  RTresult RTAPI rtContextSetPrintBufferSize(RTcontext context, RTsize  buffer_size_bytes);
  
  /**
  * @brief Get the current size of the print buffer
  * 
  * @ingroup Context
  * 
  * <B>Description</B>
  * 
  * @ref rtContextGetPrintBufferSize is used to query the buffer size available to hold
  * data generated by @ref rtPrintf. Returns @ref RT_ERROR_INVALID_VALUE if passed a \a
  * NULL pointer.
  * 
  * @param[in]   context             The context from which to query the print buffer size
  * @param[out]  buffer_size_bytes   The returned print buffer size in bytes
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtContextGetPrintBufferSize was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtPrintf,
  * @ref rtContextSetPrintEnabled,
  * @ref rtContextGetPrintEnabled,
  * @ref rtContextSetPrintBufferSize,
  * @ref rtContextSetPrintLaunchIndex,
  * @ref rtContextGetPrintLaunchIndex
  * 
  */
  RTresult RTAPI rtContextGetPrintBufferSize(RTcontext context, RTsize* buffer_size_bytes);
  
  /**
  * @brief Sets the active launch index to limit text output
  * 
  * @ingroup Context
  * 
  * <B>Description</B>
  * 
  * @ref rtContextSetPrintLaunchIndex is used to control for which launch indices @ref
  * rtPrintf generates output. The initial value of (x,y,z) is (\a -1,\a -1,\a -1), which
  * generates output for all indices.
  * 
  * @param[in]   context   The context for which to set the print launch index
  * @param[in]   x         The launch index in the x dimension to which to limit the output of @ref rtPrintf invocations.
  * If set to \a -1, output is generated for all launch indices in the x dimension
  * @param[in]   y         The launch index in the y dimension to which to limit the output of @ref rtPrintf invocations.
  * If set to \a -1, output is generated for all launch indices in the y dimension
  * @param[in]   z         The launch index in the z dimension to which to limit the output of @ref rtPrintf invocations.
  * If set to \a -1, output is generated for all launch indices in the z dimension
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtContextSetPrintLaunchIndex was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtPrintf,
  * @ref rtContextGetPrintEnabled,
  * @ref rtContextSetPrintEnabled,
  * @ref rtContextSetPrintBufferSize,
  * @ref rtContextGetPrintBufferSize,
  * @ref rtContextGetPrintLaunchIndex
  * 
  */
  RTresult RTAPI rtContextSetPrintLaunchIndex(RTcontext context, int  x, int  y, int  z);
  
  /**
  * @brief Gets the active print launch index
  * 
  * @ingroup Context
  * 
  * <B>Description</B>
  * 
  * @ref rtContextGetPrintLaunchIndex is used to query for which launch indices @ref
  * rtPrintf generates output. The initial value of (x,y,z) is (\a -1,\a -1,\a -1), which
  * generates output for all indices.
  * 
  * @param[in]   context   The context from which to query the print launch index
  * @param[out]  x         Returns the launch index in the x dimension to which the output of @ref rtPrintf invocations
  * is limited. Will not be written to if a \a NULL pointer is passed
  * @param[out]  y         Returns the launch index in the y dimension to which the output of @ref rtPrintf invocations
  * is limited. Will not be written to if a \a NULL pointer is passed
  * @param[out]  z         Returns the launch index in the z dimension to which the output of @ref rtPrintf invocations
  * is limited. Will not be written to if a \a NULL pointer is passed
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtContextGetPrintLaunchIndex was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtPrintf,
  * @ref rtContextGetPrintEnabled,
  * @ref rtContextSetPrintEnabled,
  * @ref rtContextSetPrintBufferSize,
  * @ref rtContextGetPrintBufferSize,
  * @ref rtContextSetPrintLaunchIndex
  * 
  */
  RTresult RTAPI rtContextGetPrintLaunchIndex(RTcontext context, int* x, int* y, int* z);

  /**
  * @brief Declares a new named variable associated with this
  * context
  * 
  * @ingroup Context
  * 
  * <B>Description</B>
  * 
  * @ref rtContextDeclareVariable - Declares a new variable named \a name and associated
  * with this context.  Only a single variable of a given name can exist for a given
  * context and any attempt to create multiple variables with the same name will cause a
  * failure with a return value of @ref RT_ERROR_VARIABLE_REDECLARED.  Returns @ref
  * RT_ERROR_INVALID_VALUE if passed a \a NULL pointer.  Return @ref
  * RT_ERROR_ILLEGAL_SYMBOL if \a name is not syntactically valid.
  * 
  * @param[in]   context   The context node to which the variable will be attached
  * @param[in]   name      The name that identifies the variable to be queried
  * @param[out]  v         Pointer to variable handle used to return the new object
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_VARIABLE_REDECLARED
  * 
  * <B>History</B>
  * 
  * @ref rtContextDeclareVariable was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtGeometryDeclareVariable,
  * @ref rtGeometryInstanceDeclareVariable,
  * @ref rtMaterialDeclareVariable,
  * @ref rtProgramDeclareVariable,
  * @ref rtSelectorDeclareVariable,
  * @ref rtContextGetVariable,
  * @ref rtContextGetVariableCount,
  * @ref rtContextQueryVariable,
  * @ref rtContextRemoveVariable
  * 
  */
  RTresult RTAPI rtContextDeclareVariable(RTcontext context, const char* name, RTvariable* v);
  
  /**
  * @brief Returns a named variable associated with this
  * context
  * 
  * @ingroup Context
  * 
  * <B>Description</B>
  * 
  * @ref rtContextQueryVariable queries a variable identified by the string \a name
  * from \a context and stores the result in the parameter \a v. A variable has to
  * be declared first with @ref rtContextDeclareVariable before it can be queried.
  * The return parameter \a v will be set to \a 0 if no variable exists with the given
  * name. @ref RT_ERROR_INVALID_VALUE will be returned if \a name is \a NULL.
  * 
  * @param[in]   context   The context node to query a variable from
  * @param[in]   name      The name that identifies the variable to be queried
  * @param[out]  v         Return value to store the queried variable
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtContextQueryVariable was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtGeometryQueryVariable,
  * @ref rtGeometryInstanceQueryVariable,
  * @ref rtMaterialQueryVariable,
  * @ref rtProgramQueryVariable,
  * @ref rtSelectorQueryVariable,
  * @ref rtContextDeclareVariable,
  * @ref rtContextGetVariableCount,
  * @ref rtContextGetVariable,
  * @ref rtContextRemoveVariable
  * 
  */
  RTresult RTAPI rtContextQueryVariable(RTcontext context, const char* name, RTvariable* v);
  
  /**
  * @brief Removes a variable from the given context
  * 
  * @ingroup Context
  * 
  * <B>Description</B>
  * 
  * @ref rtContextRemoveVariable removes variable \a v from \a context if present.
  * Returns @ref RT_ERROR_VARIABLE_NOT_FOUND if the variable is not attached to this
  * context. Returns @ref RT_ERROR_INVALID_VALUE if passed an invalid variable.
  * 
  * @param[in]   context   The context node from which to remove a variable
  * @param[in]   v         The variable to be removed
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_VARIABLE_NOT_FOUND
  * 
  * <B>History</B>
  * 
  * @ref rtContextRemoveVariable was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtGeometryRemoveVariable,
  * @ref rtGeometryInstanceRemoveVariable,
  * @ref rtMaterialRemoveVariable,
  * @ref rtProgramRemoveVariable,
  * @ref rtSelectorRemoveVariable,
  * @ref rtContextDeclareVariable,
  * @ref rtContextGetVariable,
  * @ref rtContextGetVariableCount,
  * @ref rtContextQueryVariable,
  * 
  */
  RTresult RTAPI rtContextRemoveVariable(RTcontext context, RTvariable v);
  
  /**
  * @brief Returns the number of variables associated
  * with this context
  * 
  * @ingroup Context
  * 
  * <B>Description</B>
  * 
  * @ref rtContextGetVariableCount returns the number of variables that are currently
  * attached to \a context.  Returns @ref RT_ERROR_INVALID_VALUE if passed a \a NULL pointer.
  * 
  * @param[in]   context   The context to be queried for number of attached variables
  * @param[out]  count     Return parameter to store the number of variables
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtContextGetVariableCount was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtGeometryGetVariableCount,
  * @ref rtGeometryInstanceGetVariableCount,
  * @ref rtMaterialGetVariableCount,
  * @ref rtProgramGetVariableCount,
  * @ref rtSelectorGetVariable,
  * @ref rtContextDeclareVariable,
  * @ref rtContextGetVariable,
  * @ref rtContextQueryVariable,
  * @ref rtContextRemoveVariable
  * 
  */
  RTresult RTAPI rtContextGetVariableCount(RTcontext context, unsigned int* count);
  
  /**
  * @brief Queries an indexed variable associated with this context
  * 
  * @ingroup Context
  * 
  * <B>Description</B>
  * 
  * @ref rtContextGetVariable queries the variable at position \a index in the
  * variable array from \a context and stores the result in the parameter \a v.
  * A variable has to be declared first with @ref rtContextDeclareVariable and
  * \a index has to be in the range [\a 0, @ref rtContextGetVariableCount \a -1].
  * 
  * @param[in]   context   The context node to be queried for an indexed variable
  * @param[in]   index     The index that identifies the variable to be queried
  * @param[out]  v         Return value to store the queried variable
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtContextGetVariable was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtGeometryGetVariable,
  * @ref rtGeometryInstanceGetVariable,
  * @ref rtMaterialGetVariable,
  * @ref rtProgramGetVariable,
  * @ref rtSelectorGetVariable,
  * @ref rtContextDeclareVariable,
  * @ref rtContextGetVariableCount,
  * @ref rtContextQueryVariable,
  * @ref rtContextRemoveVariable
  * 
  */
  RTresult RTAPI rtContextGetVariable(RTcontext context, unsigned int index, RTvariable* v);

/************************************
 **
 **    Program object
 **
 ***********************************/

  /**
  * @brief Creates a new program object
  * 
  * @ingroup Program
  * 
  * <B>Description</B>
  * 
  * @ref rtProgramCreateFromPTXString allocates and returns a handle to a new program
  * object.  The program is created from PTX code held in the \a NULL-terminated string \a
  * ptx from function \a program_name.
  * 
  * @param[in]   context        The context to create the program in
  * @param[in]   ptx            The string containing the PTX code
  * @param[in]   program_name   The name of the PTX function to create the program from
  * @param[in]   program        Handle to the program to be created
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * - @ref RT_ERROR_INVALID_SOURCE
  * 
  * <B>History</B>
  * 
  * @ref rtProgramCreateFromPTXString was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref RT_PROGRAM,
  * @ref rtProgramCreateFromPTXFile,
  * @ref rtProgramDestroy
  * 
  */
  RTresult RTAPI rtProgramCreateFromPTXString(RTcontext context, const char* ptx, const char* program_name, RTprogram* program);
  
  /**
  * @brief Creates a new program object
  * 
  * @ingroup Program
  * 
  * <B>Description</B>
  * 
  * @ref rtProgramCreateFromPTXFile allocates and returns a handle to a new program object.  
  * The program is created from PTX code held in \a filename from function \a program_name.
  * 
  * @param[in]   context        The context to create the program in
  * @param[in]   filename       Path to the file containing the PTX code
  * @param[in]   program_name   The name of the PTX function to create the program from
  * @param[in]   program        Handle to the program to be created
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * - @ref RT_ERROR_INVALID_SOURCE
  * - @ref RT_ERROR_FILE_NOT_FOUND
  * 
  * <B>History</B>
  * 
  * @ref rtProgramCreateFromPTXFile was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref RT_PROGRAM,
  * @ref rtProgramCreateFromPTXString,
  * @ref rtProgramDestroy
  * 
  */
  RTresult RTAPI rtProgramCreateFromPTXFile(RTcontext context, const char* filename, const char* program_name, RTprogram* program);
  
  /**
  * @brief Destroys a program object
  * 
  * @ingroup Program
  * 
  * <B>Description</B>
  * 
  * @ref rtProgramDestroy removes \a program from its context and deletes it.
  * \a program should be a value returned by \a rtProgramCreate*.
  * Associated variables declared via @ref rtProgramDeclareVariable are destroyed.
  * After the call, \a program is no longer a valid handle.
  * 
  * @param[in]   program   Handle of the program to destroy
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtProgramDestroy was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtProgramCreateFromPTXFile,
  * @ref rtProgramCreateFromPTXString
  * 
  */
  RTresult RTAPI rtProgramDestroy(RTprogram program);
  
  /**
  * @brief Validates the state of a program
  * 
  * @ingroup Program
  * 
  * <B>Description</B>
  * 
  * @ref rtProgramValidate checks \a program for completeness.  If \a program or any of
  * the objects attached to program are not valid, the call will return @ref
  * RT_ERROR_INVALID_CONTEXT.
  * 
  * @param[in]   program   The program to be validated
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtProgramValidate was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtProgramCreateFromPTXFile,
  * @ref rtProgramCreateFromPTXString
  * 
  */
  RTresult RTAPI rtProgramValidate(RTprogram program);
  
  /**
  * @brief Gets the context object that created a program
  * 
  * @ingroup Program
  * 
  * <B>Description</B>
  * 
  * @ref rtProgramGetContext returns a handle to the context object that was used to
  * create \a program.  If \a context is \a NULL, the call will return
  * @ref RT_ERROR_INVALID_VALUE.
  * 
  * @param[in]   program   The program to be queried for its context object
  * @param[out]  context   The return handle for the requested context object
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtProgramGetContext was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtContextCreate
  * 
  */
  RTresult RTAPI rtProgramGetContext(RTprogram program, RTcontext* context);

  /**
  * @brief Declares a new named variable associated with a program
  * 
  * @ingroup Program
  * 
  * <B>Description</B>
  * 
  * @ref rtProgramDeclareVariable declares a new variable, \a name, and associates it with
  * the program.  A variable can only be declared with the same name once on the program.
  * Any attempt to declare multiple variables with the same name will cause the call to
  * fail and return @ref RT_ERROR_VARIABLE_REDECLARED.  If \a v is \a NULL the call will
  * return @ref RT_ERROR_INVALID_VALUE.
  * 
  * @param[in]   program   The program the declared variable will be attached to
  * @param[in]   name      The name of the variable to be created
  * @param[out]  v         Return handle to the variable to be created
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * - @ref RT_ERROR_VARIABLE_REDECLARED
  * - @ref RT_ERROR_ILLEGAL_SYMBOL
  * 
  * <B>History</B>
  * 
  * @ref rtProgramDeclareVariable was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtProgramRemoveVariable,
  * @ref rtProgramGetVariable,
  * @ref rtProgramGetVariableCount,
  * @ref rtProgramQueryVariable
  * 
  */
  RTresult RTAPI rtProgramDeclareVariable(RTprogram program, const char* name, RTvariable* v);
  
  /**
  * @brief Returns a handle to the named variable attached to a program
  * 
  * @ingroup Program
  * 
  * <B>Description</B>
  * 
  * @ref rtProgramQueryVariable returns a handle to a variable object, in \a *v, attached
  * to \a program referenced by the \a NULL-terminated string \a name.  If \a name is not
  * the name of a variable attached to \a program, \a *v will be \a NULL after the call.
  * 
  * @param[in]   program   The program to be queried for the named variable
  * @param[in]   name      The name of the program to be queried for
  * @param[out]  v         The return handle to the variable object
  * @param  program   Handle to the program to be created
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtProgramQueryVariable was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtProgramDeclareVariable,
  * @ref rtProgramRemoveVariable,
  * @ref rtProgramGetVariable,
  * @ref rtProgramGetVariableCount
  * 
  */
  RTresult RTAPI rtProgramQueryVariable(RTprogram program, const char* name, RTvariable* v);
  
  /**
  * @brief Removes the named variable from a program
  * 
  * @ingroup Program
  * 
  * <B>Description</B>
  * 
  * @ref rtProgramRemoveVariable removes variable \a v from the \a program object.  Once a
  * variable has been removed from this program, another variable with the same name as
  * the removed variable may be declared.
  * 
  * @param[in]   program   The program to remove the variable from
  * @param[in]   v         The variable to remove
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * - @ref RT_ERROR_VARIABLE_NOT_FOUND
  * 
  * <B>History</B>
  * 
  * @ref rtProgramRemoveVariable was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtProgramDeclareVariable,
  * @ref rtProgramGetVariable,
  * @ref rtProgramGetVariableCount,
  * @ref rtProgramQueryVariable
  * 
  */
  RTresult RTAPI rtProgramRemoveVariable(RTprogram program, RTvariable v);
  
  /**
  * @brief Returns the number of variables attached to a program
  * 
  * @ingroup Program
  * 
  * <B>Description</B>
  * 
  * @ref rtProgramGetVariableCount returns, in \a *count, the number of variable objects that
  * have been attached to \a program.
  * 
  * @param[in]   program   The program to be queried for its variable count
  * @param[out]  count     The return handle for the number of variables attached to this program
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtProgramGetVariableCount was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtProgramDeclareVariable,
  * @ref rtProgramRemoveVariable,
  * @ref rtProgramGetVariable,
  * @ref rtProgramQueryVariable
  * 
  */
  RTresult RTAPI rtProgramGetVariableCount(RTprogram program, unsigned int* count);
  
  /**
  * @brief Returns a handle to a variable attached to a program by index
  * 
  * @ingroup Program
  * 
  * <B>Description</B>
  * 
  * @ref rtProgramGetVariable returns a handle to a variable in \a *v attached to \a
  * program with @ref rtProgramDeclareVariable by \a index.  \a index must be between
  * 0 and one less than the value returned by @ref rtProgramGetVariableCount.  The order
  * in which variables are enumerated is not constant and may change as variables are
  * attached and removed from the program object.
  * 
  * @param[in]   program   The program to be queried for the indexed variable object
  * @param[in]   index     The index of the variable to return
  * @param[out]  v         Return handle to the variable object specified by the index
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * - @ref RT_ERROR_VARIABLE_NOT_FOUND
  * 
  * <B>History</B>
  * 
  * @ref rtProgramGetVariable was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtProgramDeclareVariable,
  * @ref rtProgramRemoveVariable,
  * @ref rtProgramGetVariableCount,
  * @ref rtProgramQueryVariable
  * 
  */
  RTresult RTAPI rtProgramGetVariable(RTprogram program, unsigned int index, RTvariable* v);

  
  /**
  * @brief Returns the ID for the Program object
  * 
  * @ingroup Program
  * 
  * <B>Description</B>
  * 
  * @ref rtProgramGetId returns an ID for the provided program.  The returned ID is used
  * to reference \a program from device code.  If \a *program_id is \a NULL or the \a
  * program is not a valid RTprogram, the call will return @ref RT_ERROR_INVALID_VALUE.
  * @ref RT_PROGRAM_ID_NULL can be used as a sentinal for a non-existent program, since
  * this value will never be returned as a valid program id.
  * 
  * @param[in]   program      The program to be queried for its id
  * @param[out]  program_id   The returned ID of the program.
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtProgramGetId was introduced in OptiX 3.6.
  * 
  * <B>See also</B>
  * @ref rtContextGetProgramFromId
  *
  */
  RTresult RTAPI rtProgramGetId(RTprogram program, int* program_id);

  /**
  * @brief Gets an RTprogram corresponding to the program id
  * 
  * @ingroup Program
  * 
  * <B>Description</B>
  * 
  * @ref rtContextGetProgramFromId returns a handle to the program in \a *program
  * corresponding to the \a program_id supplied.  If \a program_id does not map to a valid
  * program handle, \a *program is \a NULL or if \a context is invalid, the call will
  * return @ref RT_ERROR_INVALID_VALUE.
  * 
  * @param[in]   context     The context the program should be originated from
  * @param[in]   program_id  The ID of the program to query
  * @param[out]  program     The return handle for the program object corresponding to the program_id
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtContextGetProgramFromId was introduced in OptiX 3.6.
  * 
  * <B>See also</B>
  * @ref rtProgramGetId
  * 
  */
  RTresult RTAPI rtContextGetProgramFromId(RTcontext context, int program_id, RTprogram* program);
  
/************************************
 **
 **    Group object
 **
 ***********************************/

  /**
  * @brief Creates a new group
  * 
  * @ingroup GroupNode
  * 
  * <B>Description</B>
  * 
  * @ref rtGroupCreate creates a new group within a context. \a context
  * specifies the target context, and should be a value returned by
  * @ref rtContextCreate.  After the call, \a *group shall be set to the handle of
  * a newly created group within \a context.
  * 
  * @param[in]   context   Specifies a context within which to create a new group
  * @param[out]  group     Returns a newly created group
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtGroupCreate was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtGroupDestroy,
  * @ref rtContextCreate
  * 
  */
  RTresult RTAPI rtGroupCreate(RTcontext context, RTgroup* group);
  
  /**
  * @brief Destroys a group node
  * 
  * @ingroup GroupNode
  * 
  * <B>Description</B>
  * 
  * @ref rtGroupDestroy removes \a group from its context and deletes it.
  * \a group should be a value returned by @ref rtGroupCreate.
  * No child graph nodes are destroyed.
  * After the call, \a group is no longer a valid handle.
  * 
  * @param[in]   group   Handle of the group node to destroy
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtGroupDestroy was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtGroupCreate
  * 
  */
  RTresult RTAPI rtGroupDestroy(RTgroup group);
  
  /**
  * @brief Verifies the state of the group
  * 
  * @ingroup GroupNode
  * 
  * <B>Description</B>
  * 
  * @ref rtGroupValidate checks \a group for completeness. If \a group or
  * any of the objects attached to \a group are not valid, the call will return
  * @ref RT_ERROR_INVALID_VALUE.
  * 
  * @param[in]   group   Specifies the group to be validated
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtGroupValidate was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtGroupCreate
  * 
  */
  RTresult RTAPI rtGroupValidate(RTgroup group);
  
  /**
  * @brief Returns the context associated with a group
  * 
  * @ingroup GroupNode
  * 
  * <B>Description</B>
  * 
  * @ref rtGroupGetContext queries a group for its associated context.
  * \a group specifies the group to query, and must be a value returned by
  * @ref rtGroupCreate. After the call, \a *context shall be set to the context
  * associated with \a group.
  * 
  * @param[in]   group     Specifies the group to query
  * @param[out]  context   Returns the context associated with the group
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtGroupGetContext was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtContextCreate,
  * @ref rtGroupCreate
  * 
  */
  RTresult RTAPI rtGroupGetContext(RTgroup group, RTcontext* context);

  /**
  * @brief Set the acceleration structure for a group
  * 
  * @ingroup GroupNode
  * 
  * <B>Description</B>
  * 
  * @ref rtGroupSetAcceleration attaches an acceleration structure to a group. The acceleration
  * structure must have been previously created using @ref rtAccelerationCreate. Every group is
  * required to have an acceleration structure assigned in order to pass validation. The acceleration
  * structure will be built over the children of the group. For example, if an acceleration structure
  * is attached to a group that has a selector, a geometry group, and a transform child,
  * the acceleration structure will be built over the bounding volumes of these three objects.
  * 
  * Note that it is legal to attach a single RTacceleration object to multiple groups, as long as
  * the underlying bounds of the children are the same. For example, if another group has three
  * children which are known to have the same bounding volumes as the ones in the example
  * above, the two groups can share an acceleration structure, thus saving build time. This is
  * true even if the details of the children, such as the actual type of a node or its geometry
  * content, differ from the first set of group children. All that is required is for a child
  * node at a given index to have the same bounds as the other group's child node at the same index.
  * 
  * Sharing an acceleration structure this way corresponds to attaching an acceleration structure
  * to multiple geometry groups at lower graph levels using @ref rtGeometryGroupSetAcceleration.
  * 
  * @param[in]   group          The group handle
  * @param[in]   acceleration   The acceleration structure to attach to the group
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtGroupSetAcceleration was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtGroupGetAcceleration,
  * @ref rtAccelerationCreate,
  * @ref rtGeometryGroupSetAcceleration
  * 
  */
  RTresult RTAPI rtGroupSetAcceleration(RTgroup group, RTacceleration  acceleration);
  
  /**
  * @brief Returns the acceleration structure attached to a group
  * 
  * @ingroup GroupNode
  * 
  * <B>Description</B>
  * 
  * @ref rtGroupGetAcceleration returns the acceleration structure attached to a group using @ref rtGroupSetAcceleration.
  * If no acceleration structure has previously been set, \a *acceleration is not written to, and @ref RT_ERROR_INVALID_VALUE is returned.
  * 
  * @param[in]   group          The group handle
  * @param[out]  acceleration   The returned acceleration structure object
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtGroupGetAcceleration was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtGroupSetAcceleration,
  * @ref rtAccelerationCreate
  * 
  */
  RTresult RTAPI rtGroupGetAcceleration(RTgroup group, RTacceleration* acceleration);

  /**
  * @brief Sets the number of child nodes to be attached to the group
  * 
  * @ingroup GroupNode
  * 
  * <B>Description</B>
  * 
  * @ref rtGroupSetChildCount specifies the number of child slots in this group. Potentially existing links to children
  * at indices greater than \a count-1 are removed. If the call increases the number of slots, the newly
  * created slots are empty and need to be filled using @ref rtGroupSetChild before validation.
  * 
  * @param[in]   group   The parent group handle
  * @param[in]   count   Number of child slots to allocate for the group
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtGroupSetChildCount was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtGroupGetChild,
  * @ref rtGroupGetChildCount,
  * @ref rtGroupGetChildType,
  * @ref rtGroupSetChild
  * 
  */
  RTresult RTAPI rtGroupSetChildCount(RTgroup group, unsigned int  count);
  
  /**
  * @brief Returns the number of child slots for a group
  * 
  * @ingroup GroupNode
  * 
  * <B>Description</B>
  * 
  * @ref rtGroupGetChildCount returns the number of child slots allocated using @ref rtGroupSetChildCount.
  * This includes empty slots which may not yet have actual children assigned by @ref rtGroupSetChild.
  * 
  * @param[in]   group   The parent group handle
  * @param[out]  count   Returned number of child slots
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtGroupGetChildCount was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtGroupSetChild,
  * @ref rtGroupGetChild,
  * @ref rtGroupSetChildCount,
  * @ref rtGroupGetChildType
  * 
  */
  RTresult RTAPI rtGroupGetChildCount(RTgroup group, unsigned int* count);
  
  /**
  * @brief Attaches a child node to a group
  * 
  * @ingroup GroupNode
  * 
  * <B>Description</B>
  * 
  * Attaches a new child node \a child to the parent node
  * \a group. \a index specifies the number of the slot where the child
  * node gets attached. A sufficient number of slots must be allocated
  * using @ref rtGroupSetChildCount.
  * Legal child node types are @ref RTgroup, @ref RTselector, @ref RTgeometrygroup, and
  * @ref RTtransform.
  * 
  * @param[in]   group   The parent group handle
  * @param[in]   index   The index in the parent's child slot array
  * @param[in]   child   The child node to be attached. Can be of type {@ref RTgroup, @ref RTselector,
  * @ref RTgeometrygroup, @ref RTtransform}
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtGroupSetChild was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtGroupSetChildCount,
  * @ref rtGroupGetChildCount,
  * @ref rtGroupGetChild,
  * @ref rtGroupGetChildType
  * 
  */
  RTresult RTAPI rtGroupSetChild(RTgroup group, unsigned int index, RTobject  child);
  
  /**
  * @brief Returns a child node of a group
  * 
  * @ingroup GroupNode
  * 
  * <B>Description</B>
  * 
  * @ref rtGroupGetChild returns the child object at slot \a index of the parent \a group.
  * If no child has been assigned to the given slot, \a *child is not written to and @ref RT_ERROR_INVALID_VALUE is returned.
  * 
  * @param[in]   group   The parent group handle
  * @param[in]   index   The index of the child slot to query
  * @param[out]  child   The returned child object
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtGroupGetChild was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtGroupSetChild,
  * @ref rtGroupSetChildCount,
  * @ref rtGroupGetChildCount,
  * @ref rtGroupGetChildType
  * 
  */
  RTresult RTAPI rtGroupGetChild(RTgroup group, unsigned int index, RTobject* child);
  
  /**
  * @brief Get the type of a group child
  * 
  * @ingroup GroupNode
  * 
  * <B>Description</B>
  * 
  * @ref rtGroupGetChildType returns the type of the group child at slot \a index.
  * If no child is associated with the given index, \a type is not written to and @ref RT_ERROR_INVALID_VALUE is returned.
  * 
  * @param[in]   group   The parent group handle
  * @param[in]   index   The index of the child slot to query
  * @param[out]  type    The returned child type
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtGroupGetChildType was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtGroupSetChild,
  * @ref rtGroupGetChild,
  * @ref rtGroupSetChildCount,
  * @ref rtGroupGetChildCount
  * 
  */
  RTresult RTAPI rtGroupGetChildType(RTgroup group, unsigned int index, RTobjecttype* type);

/************************************
 **
 **    Selector object
 **
 ***********************************/

  /**
  * @brief Creates a Selector node
  * 
  * @ingroup SelectorNode
  * 
  * <B>Description</B>
  * 
  * Creates a new Selector node within the given context. After calling
  * @ref rtSelectorCreate the new node is in a "raw" state.  For the node
  * to be functional, a visit program has to be assigned using
  * @ref rtSelectorSetVisitProgram. Furthermore, a number of (zero or
  * more) children can be attached by using @ref rtSelectorSetChildCount and
  * @ref rtSelectorSetChild.
  * 
  * @param[in]   context    Specifies the rendering context of the Selector node
  * @param[out]  selector   New Selector node handle
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtSelectorCreate was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtSelectorDestroy,
  * @ref rtSelectorValidate,
  * @ref rtSelectorGetContext,
  * @ref rtSelectorSetVisitProgram,
  * @ref rtSelectorSetChildCount,
  * @ref rtSelectorSetChild
  * 
  */
  RTresult RTAPI rtSelectorCreate(RTcontext context, RTselector* selector);
  
  /**
  * @brief Destroys a selector node
  * 
  * @ingroup SelectorNode
  * 
  * <B>Description</B>
  * 
  * @ref rtSelectorDestroy removes \a selector from its context and deletes it.
  * \a selector should be a value returned by @ref rtSelectorCreate.
  * Associated variables declared via @ref rtSelectorDeclareVariable are destroyed, but no child graph nodes are destroyed.
  * After the call, \a selector is no longer a valid handle.
  * 
  * @param[in]   selector   Handle of the selector node to destroy
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtSelectorDestroy was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtSelectorCreate,
  * @ref rtSelectorValidate,
  * @ref rtSelectorGetContext
  * 
  */
  RTresult RTAPI rtSelectorDestroy(RTselector selector);
  
  /**
  * @brief Checks a Selector node for internal consistency
  * 
  * @ingroup SelectorNode
  * 
  * <B>Description</B>
  * 
  * @ref rtSelectorValidate recursively checks consistency of the Selector
  * node \a selector and its children, i.e., it tries to validate the
  * whole model sub-tree with \a selector as root. For a Selector node to
  * be valid, it must be assigned a visit program, and the number of its
  * children must match the number specified by
  * @ref rtSelectorSetChildCount.
  * 
  * @param[in]   selector   Selector root node of a model sub-tree to be validated
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtSelectorValidate was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtSelectorCreate,
  * @ref rtSelectorDestroy,
  * @ref rtSelectorGetContext,
  * @ref rtSelectorSetVisitProgram,
  * @ref rtSelectorSetChildCount,
  * @ref rtSelectorSetChild
  * 
  */
  RTresult RTAPI rtSelectorValidate(RTselector selector);
  
  /**
  * @brief Returns the context of a Selector node
  * 
  * @ingroup SelectorNode
  * 
  * <B>Description</B>
  * 
  * @ref rtSelectorGetContext returns in \a context the rendering context
  * in which the Selector node \a selector has been created.
  * 
  * @param[in]   selector   Selector node handle
  * @param[out]  context    The context, \a selector belongs to
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtSelectorGetContext was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtSelectorCreate,
  * @ref rtSelectorDestroy,
  * @ref rtSelectorValidate
  * 
  */
  RTresult RTAPI rtSelectorGetContext(RTselector selector, RTcontext* context);

  /**
  * @brief Assigns a visit program to a Selector node
  * 
  * @ingroup SelectorNode
  * 
  * <B>Description</B>
  * 
  * @ref rtSelectorSetVisitProgram specifies a visit program that is
  * executed when the Selector node \a selector gets visited by a ray
  * during traversal of the model graph. A visit program steers how
  * traversal of the Selectors's children is performed.  It usually
  * chooses only a single child to continue traversal, but is also allowed
  * to process zero or multiple children. Programs can be created from PTX
  * files using @ref rtProgramCreateFromPTXFile.
  * 
  * @param[in]   selector   Selector node handle
  * @param[in]   program    Program handle associated with a visit program
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * - @ref RT_ERROR_TYPE_MISMATCH
  * 
  * <B>History</B>
  * 
  * @ref rtSelectorSetVisitProgram was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtSelectorGetVisitProgram,
  * @ref rtProgramCreateFromPTXFile
  * 
  */
  RTresult RTAPI rtSelectorSetVisitProgram(RTselector selector, RTprogram  program);
  
  /**
  * @brief Returns the currently assigned visit program
  * 
  * @ingroup SelectorNode
  * 
  * <B>Description</B>
  * 
  * @ref rtSelectorGetVisitProgram returns in \a program a handle of the
  * visit program curently bound to \a selector.
  * 
  * @param[in]   selector   Selector node handle
  * @param[out]  program    Current visit progam assigned to \a selector
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtSelectorGetVisitProgram was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtSelectorSetVisitProgram
  * 
  */
  RTresult RTAPI rtSelectorGetVisitProgram(RTselector selector, RTprogram* program);

  /**
  * @brief Specifies the number of child nodes to be
  * attached to a Selector node
  * 
  * @ingroup SelectorNode
  * 
  * <B>Description</B>
  * 
  * @ref rtSelectorSetChildCount allocates a number of children slots,
  * i.e., it pre-defines the exact number of child nodes the parent
  * Selector node \a selector will have.  Child nodes have to be attached
  * to the Selector node using @ref rtSelectorSetChild. Empty slots will
  * cause a validation error.
  * 
  * @param[in]   selector   Selector node handle
  * @param[in]   count      Number of child nodes to be attached to \a selector
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtSelectorSetChildCount was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtSelectorValidate,
  * @ref rtSelectorGetChildCount,
  * @ref rtSelectorSetChild,
  * @ref rtSelectorGetChild,
  * @ref rtSelectorGetChildType
  * 
  */
  RTresult RTAPI rtSelectorSetChildCount(RTselector selector, unsigned int  count);
  
  /**
  * @brief Returns the number of child node slots of
  * a Selector node
  * 
  * @ingroup SelectorNode
  * 
  * <B>Description</B>
  * 
  * @ref rtSelectorGetChildCount returns in \a count the number of child
  * node slots that have been previously reserved for the Selector node
  * \a selector by @ref rtSelectorSetChildCount. The value of \a count
  * does not reflect the actual number of child nodes that have so far
  * been attached to the Selector node using @ref rtSelectorSetChild.
  * 
  * @param[in]   selector   Selector node handle
  * @param[out]  count      Number of child node slots reserved for \a selector
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtSelectorGetChildCount was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtSelectorSetChildCount,
  * @ref rtSelectorSetChild,
  * @ref rtSelectorGetChild,
  * @ref rtSelectorGetChildType
  * 
  */
  RTresult RTAPI rtSelectorGetChildCount(RTselector selector, unsigned int* count);
  
  /**
  * @brief Attaches a child node to a Selector node
  * 
  * @ingroup SelectorNode
  * 
  * <B>Description</B>
  * 
  * Attaches a new child node \a child to the parent node
  * \a selector. \a index specifies the number of the slot where the child
  * node gets attached.  The index value must be lower than the number
  * previously set by @ref rtSelectorSetChildCount, thus it has to be in
  * the range from \a 0 to @ref rtSelectorGetChildCount \a -1.  Legal child
  * node types are @ref RTgroup, @ref RTselector, @ref RTgeometrygroup, and
  * @ref RTtransform.
  * 
  * @param[in]   selector   Selector node handle
  * @param[in]   index      Index of the parent slot the node \a child gets attached to
  * @param[in]   child      Child node to be attached. Can be {@ref RTgroup, @ref RTselector,
  * @ref RTgeometrygroup, @ref RTtransform}
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtSelectorSetChild was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtSelectorSetChildCount,
  * @ref rtSelectorGetChildCount,
  * @ref rtSelectorGetChild,
  * @ref rtSelectorGetChildType
  * 
  */
  RTresult RTAPI rtSelectorSetChild(RTselector selector, unsigned int index, RTobject  child);
  
  /**
  * @brief Returns a child node that is attached to a
  * Selector node
  * 
  * @ingroup SelectorNode
  * 
  * <B>Description</B>
  * 
  * @ref rtSelectorGetChild returns in \a child a handle of the child node
  * currently attached to \a selector at slot \a index. The index value
  * must be lower than the number previously set by
  * @ref rtSelectorSetChildCount, thus it has to be in the range from \a 0
  * to @ref rtSelectorGetChildCount \a - 1. The returned pointer is of generic
  * type @ref RTobject and needs to be cast to the actual child type, which
  * can be @ref RTgroup, @ref RTselector, @ref RTgeometrygroup, or
  * @ref RTtransform. The actual type of \a child can be queried using
  * @ref rtSelectorGetChildType;
  * 
  * @param[in]   selector   Selector node handle
  * @param[in]   index      Child node index
  * @param[out]  child      Child node handle. Can be {@ref RTgroup, @ref RTselector,
  * @ref RTgeometrygroup, @ref RTtransform}
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtSelectorGetChild was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtSelectorSetChildCount,
  * @ref rtSelectorGetChildCount,
  * @ref rtSelectorSetChild,
  * @ref rtSelectorGetChildType
  * 
  */
  RTresult RTAPI rtSelectorGetChild(RTselector selector, unsigned int index, RTobject* child);
  
  /**
  * @brief Returns type information about a Selector
  * child node
  * 
  * @ingroup SelectorNode
  * 
  * <B>Description</B>
  * 
  * @ref rtSelectorGetChildType queries the type of the child node
  * attached to \a selector at slot \a index.  The index value has to be
  * in the range from \a 0 to @ref rtSelectorGetChildCount \a - 1. The returned
  * type is one of:
  * 
  *   @ref RT_OBJECTTYPE_GROUP
  *   @ref RT_OBJECTTYPE_GEOMETRY_GROUP
  *   @ref RT_OBJECTTYPE_TRANSFORM
  *   @ref RT_OBJECTTYPE_SELECTOR
  * 
  * @param[in]   selector   Selector node handle
  * @param[in]   index      Child node index
  * @param[out]  type       Type of the child node
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtSelectorGetChildType was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtSelectorSetChildCount,
  * @ref rtSelectorGetChildCount,
  * @ref rtSelectorSetChild,
  * @ref rtSelectorGetChild
  * 
  */
  RTresult RTAPI rtSelectorGetChildType(RTselector selector, unsigned int index, RTobjecttype* type);

  /**
  * @brief Declares a variable associated with a
  * Selector node
  * 
  * @ingroup SelectorNode
  * 
  * <B>Description</B>
  * 
  * Declares a new variable identified by \a name, and associates it with
  * the Selector node \a selector. The new variable handle is returned in
  * \a v. After declaration, a variable does not have a type until its
  * value is set by an \a rtVariableSet{...} function. Once a variable
  * type has been set, it cannot be changed, i.e., only
  * \a rtVariableSet{...} functions of the same type can be used to
  * change the value of the variable.
  * 
  * @param[in]   selector   Selector node handle
  * @param[in]   name       Variable identifier
  * @param[out]  v          New variable handle
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * - @ref RT_ERROR_VARIABLE_REDECLARED
  * - @ref RT_ERROR_ILLEGAL_SYMBOL
  * 
  * <B>History</B>
  * 
  * @ref rtSelectorDeclareVariable was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtSelectorQueryVariable,
  * @ref rtSelectorRemoveVariable,
  * @ref rtSelectorGetVariableCount,
  * @ref rtSelectorGetVariable,
  * @ref rtVariableSet{...}
  * 
  */
  RTresult RTAPI rtSelectorDeclareVariable(RTselector selector, const char* name, RTvariable* v);
  
  /**
  * @brief Returns a variable associated with a
  * Selector node
  * 
  * @ingroup SelectorNode
  * 
  * <B>Description</B>
  * 
  * Returns in \a v a handle to the variable identified by \a name, which
  * is associated with the Selector node \a selector. The current value of
  * a variable can be retrieved from its handle by using an appropriate
  * \a rtVariableGet{...} function matching the variable's type.
  * 
  * @param[in]   selector   Selector node handle
  * @param[in]   name       Variable identifier
  * @param[out]  v          Variable handle
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtSelectorQueryVariable was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtSelectorDeclareVariable,
  * @ref rtSelectorRemoveVariable,
  * @ref rtSelectorGetVariableCount,
  * @ref rtSelectorGetVariable,
  * \a rtVariableGet{...}
  * 
  */
  RTresult RTAPI rtSelectorQueryVariable(RTselector selector, const char* name, RTvariable* v);
  
  /**
  * @brief Removes a variable from a Selector node
  * 
  * @ingroup SelectorNode
  * 
  * <B>Description</B>
  * 
  * @ref rtSelectorRemoveVariable removes the variable \a v from the
  * Selector node \a selector and deletes it. The handle \a v must be
  * considered invalid afterwards.
  * 
  * @param[in]   selector   Selector node handle
  * @param[in]   v          Variable handle
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * - @ref RT_ERROR_VARIABLE_NOT_FOUND
  * 
  * <B>History</B>
  * 
  * @ref rtSelectorRemoveVariable was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtSelectorDeclareVariable,
  * @ref rtSelectorQueryVariable,
  * @ref rtSelectorGetVariableCount,
  * @ref rtSelectorGetVariable
  * 
  */
  RTresult RTAPI rtSelectorRemoveVariable(RTselector selector, RTvariable v);
  
  /**
  * @brief Returns the number of variables
  * attached to a Selector node
  * 
  * @ingroup SelectorNode
  * 
  * <B>Description</B>
  * 
  * @ref rtSelectorGetVariableCount returns in \a count the number of
  * variables that are currently attached to the Selector node
  * \a selector.
  * 
  * @param[in]   selector   Selector node handle
  * @param[out]  count      Number of variables associated with \a selector
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtSelectorGetVariableCount was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtSelectorDeclareVariable,
  * @ref rtSelectorQueryVariable,
  * @ref rtSelectorRemoveVariable,
  * @ref rtSelectorGetVariable
  * 
  */
  RTresult RTAPI rtSelectorGetVariableCount(RTselector selector, unsigned int* count);
  
  /**
  * @brief Returns a variable associated with a
  * Selector node
  * 
  * @ingroup SelectorNode
  * 
  * <B>Description</B>
  * 
  * Returns in \a v a handle to the variable located at position \a index
  * in the Selectors's variable array. \a index is a sequential number
  * depending on the order of variable declarations. The index has to be
  * in the range from \a 0 to @ref rtSelectorGetVariableCount \a - 1.  The
  * current value of a variable can be retrieved from its handle by using
  * an appropriate \a rtVariableGet{...} function matching the
  * variable's type.
  * 
  * @param[in]   selector   Selector node handle
  * @param[in]   index      Variable index
  * @param[out]  v          Variable handle
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtSelectorGetVariable was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtSelectorDeclareVariable,
  * @ref rtSelectorQueryVariable,
  * @ref rtSelectorRemoveVariable,
  * @ref rtSelectorGetVariableCount,
  * \a rtVariableGet{...}
  * 
  */
  RTresult RTAPI rtSelectorGetVariable(RTselector selector, unsigned int index, RTvariable* v);

/************************************
 **
 **    Transform object
 **
 ***********************************/

  /**
  * @brief Creates a new Transform node
  * 
  * @ingroup TransformNode
  * 
  * <B>Description</B>
  * 
  * Creates a new Transform node within the given context. For the node to
  * be functional, a child node has to be attached using
  * @ref rtTransformSetChild. A transformation matrix can be associated
  * with the transform node with @ref rtTransformSetMatrix.
  * 
  * @param[in]   context    Specifies the rendering context of the Transform node
  * @param[out]  transform  New Transform node handle
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtTransformCreate was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtTransformDestroy,
  * @ref rtTransformValidate,
  * @ref rtTransformGetContext,
  * @ref rtTransformSetMatrix,
  * @ref rtTransformGetMatrix,
  * @ref rtTransformSetChild,
  * @ref rtTransformGetChild,
  * @ref rtTransformGetChildType
  * 
  */
  RTresult RTAPI rtTransformCreate(RTcontext context, RTtransform* transform);
  
  /**
  * @brief Destroys a transform node
  * 
  * @ingroup TransformNode
  * 
  * <B>Description</B>
  * 
  * @ref rtTransformDestroy removes \a transform from its context and deletes it.
  * \a transform should be a value returned by @ref rtTransformCreate.
  * No child graph nodes are destroyed.
  * After the call, \a transform is no longer a valid handle.
  * 
  * @param[in]   transform   Handle of the transform node to destroy
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtTransformDestroy was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtTransformCreate,
  * @ref rtTransformValidate,
  * @ref rtTransformGetContext
  * 
  */
  RTresult RTAPI rtTransformDestroy(RTtransform transform);
  
  /**
  * @brief Checks a Transform node for internal
  * consistency
  * 
  * @ingroup TransformNode
  * 
  * <B>Description</B>
  * 
  * @ref rtTransformValidate recursively checks consistency of the
  * Transform node \a transform and its child, i.e., it tries to validate
  * the whole model sub-tree with \a transform as root. For a Transform
  * node to be valid, it must have a child node attached. It is, however,
  * not required to explicitly set a transformation matrix. Without a specified
  * transformation matrix, the identity matrix is applied.
  * 
  * @param[in]   transform   Transform root node of a model sub-tree to be validated
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtTransformValidate was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtTransformCreate,
  * @ref rtTransformDestroy,
  * @ref rtTransformGetContext,
  * @ref rtTransformSetMatrix,
  * @ref rtTransformSetChild
  * 
  */
  RTresult RTAPI rtTransformValidate(RTtransform transform);
  
  /**
  * @brief Returns the context of a Transform node
  * 
  * @ingroup TransformNode
  * 
  * <B>Description</B>
  * 
  * @ref rtTransformGetContext queries a transform node for its associated context.
  * \a transform specifies the transform node to query, and should be a value returned by
  * @ref rtTransformCreate. After the call, \a *context shall be set to the context
  * associated with \a transform.
  * 
  * @param[in]   transform   Transform node handle
  * @param[out]  context     The context associated with \a transform
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtTransformGetContext was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtTransformCreate,
  * @ref rtTransformDestroy,
  * @ref rtTransformValidate
  * 
  */
  RTresult RTAPI rtTransformGetContext(RTtransform transform, RTcontext* context);

  /**
  * @brief Associates an affine transformation matrix
  * with a Transform node
  * 
  * @ingroup TransformNode
  * 
  * <B>Description</B>
  * 
  * @ref rtTransformSetMatrix associates a 4x4 matrix with the Transform
  * node \a transform. The provided transformation matrix results in a
  * corresponding affine transformation of all geometry contained in the
  * sub-tree with \a transform as root. At least one of the pointers
  * \a matrix and \a inverse_matrix must be non-\a NULL. If exactly one
  * pointer is valid, the other matrix will be computed. If both are
  * valid, the matrices will be used as-is. If \a transpose is \a 0,
  * source matrices are expected to be in row-major format, i.e., matrix
  * rows are contiguously laid out in memory:
  * 
  *   float matrix[4*4] = { a11,  a12,  a13,  a14, 
  *                         a21,  a22,  a23,  a24, 
  *                         a31,  a32,  a33,  a34, 
  *                         a41,  a42,  a43,  a44 }; 
  * 
  * Here, the translational elements \a a14, \a a24, and \a a34 are at the
  * 4th, 8th, and 12th position the matrix array.  If the supplied
  * matrices are in column-major format, a non-0 \a transpose flag
  * can be used to trigger an automatic transpose of the input matrices.
  * 
  * @param[in]   transform        Transform node handle
  * @param[in]   transpose        Flag indicating whether \a matrix and \a inverse_matrix should be
  * transposed
  * @param[in]   matrix           Affine matrix (4x4 float array)
  * @param[in]   inverse_matrix   Inverted form of \a matrix
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtTransformSetMatrix was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtTransformGetMatrix
  * 
  */
  RTresult RTAPI rtTransformSetMatrix(RTtransform transform, int transpose, const float* matrix, const float* inverse_matrix);
  
  /**
  * @brief Returns the affine matrix and its inverse associated with a Transform node
  * 
  * @ingroup TransformNode
  * 
  * <B>Description</B>
  * 
  * @ref rtTransformGetMatrix returns in \a matrix the affine matrix that
  * is currently used to perform a transformation of the geometry
  * contained in the sub-tree with \a transform as root. The corresponding
  * inverse matrix will be retured in \a inverse_matrix. One or both
  * pointers are allowed to be \a NULL. If \a transpose is \a 0, matrices
  * are returned in row-major format, i.e., matrix rows are contiguously
  * laid out in memory. If \a transpose is non-zero, matrices are returned
  * in column-major format. If non-\a NULL, matrix pointers must point to a
  * float array of at least 16 elements.
  * 
  * @param[in]   transform        Transform node handle
  * @param[in]   transpose        Flag indicating whether \a matrix and \a inverse_matrix should be
  * transposed
  * @param[out]  matrix           Affine matrix (4x4 float array)
  * @param[out]  inverse_matrix   Inverted form of \a matrix
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtTransformGetMatrix was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtTransformSetMatrix
  * 
  */
  RTresult RTAPI rtTransformGetMatrix(RTtransform transform, int transpose, float* matrix, float* inverse_matrix);

  /**
  * @brief Attaches a child node to a Transform node
  * 
  * @ingroup TransformNode
  * 
  * <B>Description</B>
  * 
  * Attaches a child node \a child to the parent node \a transform. Legal
  * child node types are @ref RTgroup, @ref RTselector, @ref RTgeometrygroup,
  * and @ref RTtransform. A transform node must have exactly one child.  If
  * a tranformation matrix has been attached to \a transform with
  * @ref rtTransformSetMatrix, it is effective on the model sub-tree with
  * \a child as root node.
  * 
  * @param[in]   transform   Transform node handle
  * @param[in]   child       Child node to be attached. Can be {@ref RTgroup, @ref RTselector,
  * @ref RTgeometrygroup, @ref RTtransform}
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtTransformSetChild was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtTransformSetMatrix,
  * @ref rtTransformGetChild,
  * @ref rtTransformGetChildType
  * 
  */
  RTresult RTAPI rtTransformSetChild(RTtransform transform, RTobject  child);
  
  /**
  * @brief Returns the child node that is attached to a
  * Transform node
  * 
  * @ingroup TransformNode
  * 
  * <B>Description</B>
  * 
  * @ref rtTransformGetChild returns in \a child a handle of the child
  * node currently attached to \a transform. The returned pointer is of
  * generic type @ref RTobject and needs to be cast to the actual child
  * type, which can be @ref RTgroup, @ref RTselector, @ref RTgeometrygroup, or
  * @ref RTtransform. The actual type of \a child can be queried using
  * @ref rtTransformGetChildType.
  * 
  * @param[in]   transform   Transform node handle
  * @param[out]  child       Child node handle. Can be {@ref RTgroup, @ref RTselector,
  * @ref RTgeometrygroup, @ref RTtransform}
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtTransformGetChild was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtTransformSetChild,
  * @ref rtTransformGetChildType
  * 
  */
  RTresult RTAPI rtTransformGetChild(RTtransform transform, RTobject* child);
  
  /**
  * @brief Returns type information about a
  * Transform child node
  * 
  * @ingroup TransformNode
  * 
  * <B>Description</B>
  * 
  * @ref rtTransformGetChildType queries the type of the child node
  * attached to \a selector. The returned type is one of:
  * 
  *  - @ref RT_OBJECTTYPE_GROUP
  *  - @ref RT_OBJECTTYPE_GEOMETRY_GROUP
  *  - @ref RT_OBJECTTYPE_TRANSFORM
  *  - @ref RT_OBJECTTYPE_SELECTOR
  * 
  * @param[in]   transform   Transform node handle
  * @param[out]  type        Type of the child node
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtTransformGetChildType was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtTransformSetChild,
  * @ref rtTransformGetChild
  * 
  */
  RTresult RTAPI rtTransformGetChildType(RTtransform transform, RTobjecttype* type);

/************************************
 **
 **    GeometryGroup object
 **
 ***********************************/

  /**
  * @brief Creates a new geometry group
  * 
  * @ingroup GeometryGroup
  * 
  * <B>Description</B>
  * 
  * @ref rtGeometryGroupCreate creates a new geometry group within a context. \a context
  * specifies the target context, and should be a value returned by
  * @ref rtContextCreate.  After the call, \a *geometrygroup shall be set to the handle of
  * a newly created group within \a context.
  * 
  * @param[in]   context         Specifies a context within which to create a new geometry group
  * @param[out]  geometrygroup   Returns a newly created geometry group
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtGeometryGroupCreate was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtGeometryGroupDestroy,
  * @ref rtContextCreate
  * 
  */
  RTresult RTAPI rtGeometryGroupCreate(RTcontext context, RTgeometrygroup* geometrygroup);
  
  /**
  * @brief Destroys a geometry group node
  * 
  * @ingroup GeometryGroup
  * 
  * <B>Description</B>
  * 
  * @ref rtGeometryGroupDestroy removes \a geometrygroup from its context and deletes it.
  * \a geometrygroup should be a value returned by @ref rtGeometryGroupCreate.
  * No child graph nodes are destroyed.
  * After the call, \a geometrygroup is no longer a valid handle.
  * 
  * @param[in]   geometrygroup   Handle of the geometry group node to destroy
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtGeometryGroupDestroy was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtGeometryGroupCreate
  * 
  */
  RTresult RTAPI rtGeometryGroupDestroy(RTgeometrygroup geometrygroup);
  
  /**
  * @brief Validates the state of the geometry group
  * 
  * @ingroup GeometryGroup
  * 
  * <B>Description</B>
  * 
  * @ref rtGeometryGroupValidate checks \a geometrygroup for completeness. If \a geometrygroup or
  * any of the objects attached to \a geometrygroup are not valid, the call will return
  * @ref RT_ERROR_INVALID_VALUE.
  * 
  * @param[in]   geometrygroup   Specifies the geometry group to be validated
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtGeometryGroupValidate was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtGeometryGroupCreate
  * 
  */
  RTresult RTAPI rtGeometryGroupValidate(RTgeometrygroup geometrygroup);
  
  /**
  * @brief Returns the context associated with a geometry group
  * 
  * @ingroup GeometryGroup
  * 
  * <B>Description</B>
  * 
  * @ref rtGeometryGroupGetContext queries a geometry group for its associated context.
  * \a geometrygroup specifies the geometry group to query, and must be a value returned by
  * @ref rtGeometryGroupCreate. After the call, \a *context shall be set to the context
  * associated with \a geometrygroup.
  * 
  * @param[in]   geometrygroup   Specifies the geometry group to query
  * @param[out]  context         Returns the context associated with the geometry group
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtGeometryGroupGetContext was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtContextCreate,
  * @ref rtGeometryGroupCreate
  * 
  */
  RTresult RTAPI rtGeometryGroupGetContext(RTgeometrygroup geometrygroup, RTcontext* context);

  /**
  * @brief Set the acceleration structure for a group
  * 
  * @ingroup GeometryGroup
  * 
  * <B>Description</B>
  * 
  * @ref rtGeometryGroupSetAcceleration attaches an acceleration structure to a geometry group. The acceleration
  * structure must have been previously created using @ref rtAccelerationCreate. Every geometry group is
  * required to have an acceleration structure assigned in order to pass validation. The acceleration structure
  * will be built over the primitives contained in all children of the geometry group. This enables a single acceleration
  * structure to be built over primitives of multiple geometry instances.
  * Note that it is legal to attach a single RTacceleration object to multiple geometry groups, as long as
  * the underlying geometry of all children is the same. This corresponds to attaching an acceleration structure
  * to multiple groups at higher graph levels using @ref rtGroupSetAcceleration.
  * 
  * @param[in]   geometrygroup   The geometry group handle
  * @param[in]   acceleration    The acceleration structure to attach to the geometry group
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtGeometryGroupSetAcceleration was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtGeometryGroupGetAcceleration,
  * @ref rtAccelerationCreate,
  * @ref rtGroupSetAcceleration
  * 
  */
  RTresult RTAPI rtGeometryGroupSetAcceleration(RTgeometrygroup geometrygroup, RTacceleration  acceleration);
  
  /**
  * @brief Returns the acceleration structure attached to a geometry group
  * 
  * @ingroup GeometryGroup
  * 
  * <B>Description</B>
  * 
  * @ref rtGeometryGroupGetAcceleration returns the acceleration structure attached to a geometry group using @ref rtGeometryGroupSetAcceleration.
  * If no acceleration structure has previously been set, \a *acceleration is not written to, and @ref RT_ERROR_INVALID_VALUE is returned.
  * 
  * @param[in]   geometrygroup   The geometry group handle
  * @param[out]  acceleration    The returned acceleration structure object
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtGeometryGroupGetAcceleration was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtGeometryGroupSetAcceleration,
  * @ref rtAccelerationCreate
  * 
  */
  RTresult RTAPI rtGeometryGroupGetAcceleration(RTgeometrygroup geometrygroup, RTacceleration* acceleration);

  /**
  * @brief Sets the number of child nodes to be attached to the group
  * 
  * @ingroup GeometryGroup
  * 
  * <B>Description</B>
  * 
  * @ref rtGeometryGroupSetChildCount specifies the number of child slots in this geometry group. Potentially existing links to children
  * at indices greater than \a count-1 are removed. If the call increases the number of slots, the newly
  * created slots are empty and need to be filled using @ref rtGeometryGroupSetChild before validation.
  * 
  * @param[in]   geometrygroup   The parent geometry group handle
  * @param[in]   count           Number of child slots to allocate for the geometry group
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtGeometryGroupSetChildCount was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtGeometryGroupGetChild,
  * @ref rtGeometryGroupGetChildCount
  * @ref rtGeometryGroupSetChild
  * 
  */
  RTresult RTAPI rtGeometryGroupSetChildCount(RTgeometrygroup geometrygroup, unsigned int  count);
  
  /**
  * @brief Returns the number of child slots for a group
  * 
  * @ingroup GeometryGroup
  * 
  * <B>Description</B>
  * 
  * @ref rtGeometryGroupGetChildCount returns the number of child slots allocated using @ref rtGeometryGroupSetChildCount.
  * This includes empty slots which may not yet have actual children assigned by @ref rtGeometryGroupSetChild.
  * 
  * @param[in]   geometrygroup   The parent geometry group handle
  * @param[out]  count           Returned number of child slots
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtGeometryGroupGetChildCount was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtGeometryGroupSetChild,
  * @ref rtGeometryGroupGetChild,
  * @ref rtGeometryGroupSetChildCount
  * 
  */
  RTresult RTAPI rtGeometryGroupGetChildCount(RTgeometrygroup geometrygroup, unsigned int* count);
  
  /**
  * @brief Attaches a child node to a geometry group
  * 
  * @ingroup GeometryGroup
  * 
  * <B>Description</B>
  * 
  * @ref rtGeometryGroupSetChild attaches a new child node \a geometryinstance to the parent node
  * \a geometrygroup. \a index specifies the number of the slot where the child
  * node gets attached.  The index value must be lower than the number
  * previously set by @ref rtGeometryGroupSetChildCount.
  * 
  * @param[in]   geometrygroup      The parent geometry group handle
  * @param[in]   index              The index in the parent's child slot array
  * @param[in]   geometryinstance   The child node to be attached
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtGeometryGroupSetChild was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtGeometryGroupSetChildCount,
  * @ref rtGeometryGroupGetChildCount,
  * @ref rtGeometryGroupGetChild
  * 
  */
  RTresult RTAPI rtGeometryGroupSetChild(RTgeometrygroup geometrygroup, unsigned int index, RTgeometryinstance  geometryinstance);
  
  /**
  * @brief Returns a child node of a geometry group
  * 
  * @ingroup GeometryGroup
  * 
  * <B>Description</B>
  * 
  * @ref rtGeometryGroupGetChild returns the child geometry instance at slot \a index of the parent \a geometrygroup.
  * If no child has been assigned to the given slot, \a *child is not written to and @ref RT_ERROR_INVALID_VALUE is returned.
  * 
  * @param[in]   geometrygroup      The parent geometry group handle
  * @param[in]   index              The index of the child slot to query
  * @param[out]  geometryinstance   The returned child geometry instance
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtGeometryGroupGetChild was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtGeometryGroupSetChild,
  * @ref rtGeometryGroupSetChildCount,
  * @ref rtGeometryGroupGetChildCount,
  * 
  */
  RTresult RTAPI rtGeometryGroupGetChild(RTgeometrygroup geometrygroup, unsigned int index, RTgeometryinstance* geometryinstance);

/************************************
 **
 **    Acceleration object
 **
 ***********************************/

  /**
  * @brief Creates a new acceleration structure
  * 
  * @ingroup AccelerationStructure
  * 
  * <B>Description</B>
  * 
  * @ref rtAccelerationCreate creates a new ray tracing acceleration structure within a context.
  * An acceleration structure is used by attaching it to a group or geometry group by calling
  * @ref rtGroupSetAcceleration or @ref rtGeometryGroupSetAcceleration. Note that an acceleration
  * structure can be shared by attaching it to multiple groups or geometry groups if the underlying
  * geometric structures are the same, see @ref rtGroupSetAcceleration and @ref rtGeometryGroupSetAcceleration for more details.
  * A newly created acceleration structure is initially in dirty state.
  * 
  * @param[in]   context        Specifies a context within which to create a new acceleration structure
  * @param[out]  acceleration   Returns the newly created acceleration structure
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtAccelerationCreate was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtAccelerationDestroy,
  * @ref rtContextCreate,
  * @ref rtAccelerationMarkDirty,
  * @ref rtAccelerationIsDirty,
  * @ref rtGroupSetAcceleration,
  * @ref rtGeometryGroupSetAcceleration
  * 
  */
  RTresult RTAPI rtAccelerationCreate(RTcontext context, RTacceleration* acceleration);
  
  /**
  * @brief Destroys an acceleration structure object
  * 
  * @ingroup AccelerationStructure
  * 
  * <B>Description</B>
  * 
  * @ref rtAccelerationDestroy removes \a acceleration from its context and deletes it.
  * \a acceleration should be a value returned by @ref rtAccelerationCreate.
  * After the call, \a acceleration is no longer a valid handle.
  * 
  * @param[in]   acceleration   Handle of the acceleration structure to destroy
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtAccelerationDestroy was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtAccelerationCreate
  * 
  */
  RTresult RTAPI rtAccelerationDestroy(RTacceleration acceleration);
  
  /**
  * @brief Validates the state of an acceleration structure
  * 
  * @ingroup AccelerationStructure
  * 
  * <B>Description</B>
  * 
  * @ref rtAccelerationValidate checks \a acceleration for completeness. If \a acceleration is
  * not valid, the call will return @ref RT_ERROR_INVALID_VALUE.
  * 
  * @param[in]   acceleration   The acceleration structure handle
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtAccelerationValidate was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtAccelerationCreate
  * 
  */
  RTresult RTAPI rtAccelerationValidate(RTacceleration acceleration);
  
  /**
  * @brief Returns the context associated with an acceleration structure
  * 
  * @ingroup AccelerationStructure
  * 
  * <B>Description</B>
  * 
  * @ref rtAccelerationGetContext queries an acceleration structure for its associated context.
  * The context handle is returned in the location pointed to by \a context.
  * 
  * @param[in]   acceleration   The acceleration structure handle
  * @param[out]  context        Returns the context associated with the acceleration structure
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtAccelerationGetContext was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtAccelerationCreate
  * 
  */
  RTresult RTAPI rtAccelerationGetContext(RTacceleration acceleration, RTcontext* context);
  

  /**
  * @brief Specifies the builder to be used for an acceleration structure
  * 
  * @ingroup AccelerationStructure
  * 
  * <B>Description</B>
  * 
  * @ref rtAccelerationSetBuilder specifies the method used to construct the ray tracing acceleration structure
  * represented by \a acceleration. A builder has to be set for the acceleration structure to pass validation.
  * The current builder can be changed at any time, including after a call to @ref rtContextLaunch "rtContextLaunch".
  * In this case, data previously computed
  * for the acceleration structure is invalidated and the acceleration will be marked dirty.
  * 
  * An acceleration structure is only valid with a correct pair of builder and traverser. The traverser type
  * is specified using @ref rtAccelerationSetTraverser. For a list of valid combinations of builders and traversers, see below. For a description of the individual traversers, see @ref rtAccelerationSetTraverser.
  * 
  * \a builder can take one of the following values:
  * 
  * - "NoAccel": Specifies that no acceleration structure is explicitly built. Traversal linearly loops through the
  * list of primitives to intersect. This can be useful e.g. for higher level groups with only few children, where managing a more complex structure introduces unnecessary overhead. Valid traverser types: "NoAccel".
  * 
  * - "Bvh": A standard bounding volume hierarchy, useful for most types of graph levels and geometry. Medium build speed, good ray tracing performance. Valid traverser types: "Bvh", "BvhCompact".
  * 
  * - "Sbvh": A high quality BVH variant for maximum ray tracing performance. Slower build speed and slightly higher memory footprint than "Bvh". Valid traverser types: "Bvh", "BvhCompact".
  * 
  * - "MedianBvh": A medium quality bounding volume hierarchy with quick build performance. Useful for dynamic and semi-dynamic
  * content. Valid traverser types: "Bvh", "BvhCompact".
  * 
  * - "Lbvh": A simple bounding volume hierarchy with very fast build performance. Useful for dynamic content. Valid traverser types: "Bvh", "BvhCompact".
  *
  * - "Trbvh": High quality similar to Sbvh but with fast build performance similar to Lbvh. Valid traverser types: "Bvh". Temporarily, the Trbvh builder uses about three times the size of the final BVH for scratch space. OptiX Commercial includes a CPU-based Trbvh builder that does not have the memory constraints, and an optional automatic fallback to the CPU version when out of GPU memory. See details in section 3.5 of the programming guide.
  * 
  * - "TriangleKdTree": A high quality kd-tree builder, for triangle geometry only. This may provide better ray tracing performance than the BVH builders for some scenarios. Valid traverser types: "KdTree".
  * 
  * @param[in]   acceleration   The acceleration structure handle
  * @param[in]   builder        String value specifying the builder type
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtAccelerationSetBuilder was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtAccelerationGetBuilder,
  * @ref rtAccelerationSetTraverser,
  * @ref rtAccelerationSetProperty
  * 
  */
  RTresult RTAPI rtAccelerationSetBuilder(RTacceleration acceleration, const char* builder);
  
  /**
  * @brief Query the current builder from an acceleration structure
  * 
  * @ingroup AccelerationStructure
  * 
  * <B>Description</B>
  * 
  * @ref rtAccelerationGetBuilder returns the name of the builder currently
  * used in the acceleration structure \a acceleration. If no builder has
  * been set for \a acceleration, an empty string is returned.
  * \a return_string will be set to point to the returned string. The
  * memory \a return_string points to will be valid until the next API
  * call that returns a string.
  * 
  * @param[in]   acceleration    The acceleration structure handle
  * @param[out]  return_string   Return string buffer
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtAccelerationGetBuilder was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtAccelerationSetBuilder
  * 
  */
  RTresult RTAPI rtAccelerationGetBuilder(RTacceleration acceleration, const char** return_string);
  
  /**
  * @brief Specifies the traverser to be used for an acceleration structure
  * 
  * @ingroup AccelerationStructure
  * 
  * <B>Description</B>
  * 
  * @ref rtAccelerationSetTraverser specifies the method used to traverse the ray tracing acceleration structure
  * represented by \a acceleration. A traverser has to be set for the acceleration structure to pass validation.
  * The current active traverser can be changed at any time.
  * 
  * An acceleration structure is only valid with a correct pair of builder and traverser. The builder type
  * is specified using @ref rtAccelerationSetBuilder. For a list of valid combinations of builders and traversers, see below. For a description of the individual builders, see @ref rtAccelerationSetBuilder.
  * 
  * \a traverser can take one of the following values:
  * 
  * - "NoAccel": Linearly loops through the list of primitives to intersect. This is highly inefficient in all but
  * the most trivial scenarios (but there it can provide good performance due to very little overhead).
  * Valid builder types: "NoAccel".
  * 
  * - "Bvh": Optimized traversal of generic bounding volume hierarchies.
  * Valid builder types: "Trbvh", "Sbvh", "Bvh", "MedianBvh", "Lbvh".
  * 
  * - "BvhCompact": Optimized traversal of bounding volume hierarchies
  * for large datasets when virtual memory is turned on. 
  * It compresses the BVH data in 4 times before uploading to 
  * the device. And decompress the BVH data in real-time during traversal of 
  * a bounding volume hierarchy. 
  * Valid builder types: "Sbvh", "Bvh", "MedianBvh", "Lbvh".
  * 
  * - "KdTree": Standard traversal for kd-trees.
  * Valid builder types: "TriangleKdTree".
  * 
  * @param[in]   acceleration   The acceleration structure handle
  * @param[in]   traverser      String value specifying the traverser type
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtAccelerationSetTraverser was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtAccelerationGetTraverser,
  * @ref rtAccelerationSetBuilder,
  * @ref rtAccelerationSetProperty
  * 
  */
  RTresult RTAPI rtAccelerationSetTraverser(RTacceleration acceleration, const char* traverser);
  
  /**
  * @brief Query the current traverser from an acceleration structure
  * 
  * @ingroup AccelerationStructure
  * 
  * <B>Description</B>
  * 
  * @ref rtAccelerationGetTraverser returns the name of the traverser
  * currently used in the acceleration structure \a acceleration.  If no
  * traverser has been set for \a acceleration, an empty string is
  * returned. \a return_string will be set to point to the returned
  * string. The memory \a return_string points to will be valid until the
  * next API call that returns a string.
  * 
  * @param[in]   acceleration    The acceleration structure handle
  * @param[out]  return_string   Return string buffer
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtAccelerationGetTraverser was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtAccelerationSetTraverser
  * 
  */
  RTresult RTAPI rtAccelerationGetTraverser(RTacceleration acceleration, const char** return_string);
  
  /**
  * @brief Sets an acceleration structure property
  * 
  * @ingroup AccelerationStructure
  * 
  * <B>Description</B>
  * 
  * @ref rtAccelerationSetProperty sets a named property value for an
  * acceleration structure. Properties can be used to fine tune the way an
  * acceleration structure is built, in order to achieve faster build
  * times or better ray tracing performance.  Properties are evaluated and
  * applied by the acceleration structure during build time, and
  * different builders recognize different properties. Setting a property
  * will never fail as long as \a acceleration is a valid
  * handle. Properties that are not recognized by an acceleration
  * structure will be ignored.
  * 
  * The following is a list of the properties used by the individual builders:
  * 
  * - "NoAccel": No properties are available for this builder.
  * 
  * - "Bvh": \b refit is an integer value specifying whether the BVH should be refitted
  * or rebuilt from scratch when a valid BVH over
  * similar geometry is already existent. The value indicates how many frames are to pass
  * before forcing a rebuild, the exception being a value of 1, which will always refit
  * (never rebuild if possible). A value of 0 will never refit (always rebuild).
  * Regardless of the refit value, if the number of primitives changes from the last
  * frame, a rebuild is forced. Refitting is much faster than a full
  * rebuild, and usually yields good ray tracing performance if deformations
  * to the underlying geometry are not too large. The default is 0. refit is only
  * supported on SM_20 (Fermi) class GPUs and later. Older devices will simply ignore the
  * refit property, effectively rebuilding any time the structure is marked dirty.
  * \b refine can be used in combination with refit, and will apply tree rotations
  * to the existing BVH to attempt to improve the quality for faster traversal. Like refit, 
  * tree rotations are much faster than a full rebuild. The value indicates
  * how many rotation passes over the tree to perform per frame. With \b refine on, 
  * the quality of the tree degrades much less rapidly than with just refit, and can
  * increase the number of frames between rebuilds before traversal performance suffers. 
  * In some cases, it can eliminate the need for rebuilds entirely. The default is 0.
  * refine is only supported on SM_20 (Fermi) class GPUs and later.
  * 
  * - "Sbvh": The SBVH can be used for any type of geometry, but especially efficient structures
  * can be built for triangles. For this case, the following properties are used
  * in order to provide the necessary geometry information to the acceleration object:
  * \b vertex_buffer_name specifies the name of the vertex buffer variable for
  * underlying geometry, containing float3 vertices. \b vertex_buffer_stride
  * is used to define the offset between two vertices in the buffer, given in
  * bytes. The default stride is zero, which assumes that the vertices are
  * tightly packed.
  * \b index_buffer_name specifies the name of the index buffer
  * variable for underlying geometry (if any). The entries in this buffer are
  * indices of type int, where each index refers to one entry in the vertex buffer.
  * A sequence of three indices represent one triangle.
  * \b index_buffer_stride can be used analog to \b vertex_buffer_stride to
  * describe interleaved arrays.
  * 
  * - "MedianBvh": \b refit (see \b refit flag for "Bvh" above).
  * \b refine, (see \b refine flag for "Bvh" above).
  * 
  * - "Lbvh": \b refit (see \b refit flag for "Bvh" above).
  * \b refine, (see refine flag for "Bvh" above), with one important difference: 
  * for "Lbvh", \b refine can be used alone, and does not require \b refit.
  * If used without \b refit, tree rotations will be applied after the Lbvh build. 
  * The default is 0.
  * 
  * - "Trbvh": Similar in quality to Sbvh but builds much faster. Builds on the GPU and is
  * subject to GPU memory constraints, including, temporarily, requiring scratch space about three
  * times as large as the final data structure. See section 3.5 of the programming guide for details.
  * See Sbvh for a description of the relevant properties (\b vertex_buffer_name, 
  * \b index_buffer_name, \b vertex_buffer_stride, and \b index_buffer_stride).
  * 
  * - "TriangleKdTree": Since the kd-tree can build its acceleration structure over triangles only,
  * the geometry data and its format must be made available to the acceleration
  * object. See Sbvh for a description of the relevant properties
  * (\b vertex_buffer_name, \b index_buffer_name, \b vertex_buffer_stride,
  * and \b index_buffer_stride).
  * 
  * @param[in]   acceleration   The acceleration structure handle
  * @param[in]   name           String value specifying the name of the property
  * @param[in]   value          String value specifying the value of the property
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtAccelerationSetProperty was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtAccelerationGetProperty,
  * @ref rtAccelerationSetBuilder,
  * @ref rtAccelerationSetTraverser
  * 
  */
  RTresult RTAPI rtAccelerationSetProperty(RTacceleration acceleration, const char* name, const char* value);
  
  /**
  * @brief Queries an acceleration structure property
  * 
  * @ingroup AccelerationStructure
  * 
  * <B>Description</B>
  * 
  * @ref rtAccelerationGetProperty returns the value of the acceleration
  * structure property \a name.  See @ref rtAccelerationSetProperty for a
  * list of supported properties.  If the property name is not found, an
  * empty string is returned.  \a return_string will be set to point to
  * the returned string. The memory \a return_string points to will be
  * valid until the next API call that returns a string.
  * 
  * @param[in]   acceleration    The acceleration structure handle
  * @param[in]   name            The name of the property to be queried
  * @param[out]  return_string   Return string buffer
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtAccelerationGetProperty was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtAccelerationSetProperty,
  * @ref rtAccelerationSetBuilder,
  * @ref rtAccelerationSetTraverser
  * 
  */
  RTresult RTAPI rtAccelerationGetProperty(RTacceleration acceleration, const char* name, const char** return_string);

  /**
  * @brief Returns the size of the data to be retrieved from an acceleration structure
  * 
  * @ingroup AccelerationStructure
  * 
  * <B>Description</B>
  * 
  * @ref rtAccelerationGetDataSize queries the size of the data that will be returned on a subsequent
  * call to @ref rtAccelerationGetData. The size in bytes will be written to the location pointed to by \a size.
  * The returned value is guaranteed to be valid only if no other function using the handle \a acceleration
  * is made before @ref rtAccelerationGetData.
  * 
  * If \a acceleration is marked dirty, this call is invalid and will return @ref RT_ERROR_INVALID_VALUE.
  * 
  * @param[in]   acceleration   The acceleration structure handle
  * @param[out]  size           The returned size of the data in bytes
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtAccelerationGetDataSize was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtAccelerationGetData,
  * @ref rtAccelerationSetData
  * 
  */
  RTresult RTAPI rtAccelerationGetDataSize(RTacceleration acceleration, RTsize* size);
  
  /**
  * @brief Retrieves acceleration structure data
  * 
  * @ingroup AccelerationStructure
  * 
  * <B>Description</B>
  * 
  * @ref rtAccelerationGetData retrieves the full state of the \a acceleration object,
  * and copies it to the memory region pointed to by \a data. Sufficient memory must be available
  * starting at that location to hold the entire state. To query the required memory size,
  * @ref rtAccelerationGetDataSize should be used.
  * 
  * The returned \a data from this call is valid input data for @ref rtAccelerationSetData.
  * 
  * If \a acceleration is marked dirty, this call is invalid and will return @ref RT_ERROR_INVALID_VALUE.
  * 
  * @param[in]   acceleration   The acceleration structure handle
  * @param[out]  data           Pointer to a memory region to be filled with the state of \a acceleration
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtAccelerationGetData was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtAccelerationSetData,
  * @ref rtAccelerationGetDataSize
  * 
  */
  RTresult RTAPI rtAccelerationGetData(RTacceleration acceleration, void* data);
  
  /**
  * @brief Sets the state of an acceleration structure
  * 
  * @ingroup AccelerationStructure
  * 
  * <B>Description</B>
  * 
  * @ref rtAccelerationSetData sets the full state of the \a acceleration
  * object, including builder and traverser type as well as properties, as
  * defined by \a data.  The memory pointed to by \a data must be
  * unaltered values previously retrieved from a (potentially different)
  * acceleration structure handle. This mechanism is useful for
  * implementing caching mechanisms, especially when using high quality
  * structures which are expensive to build.
  * 
  * Note that no check is performed on whether the contents of \a data match the actual
  * underlying geometry on which the acceleration structure is used. If the children of
  * associated groups or geometry groups differ in number of children, layout of bounding boxes,
  * or geometry, then behavior after this call is undefined.
  * 
  * This call returns @ref RT_ERROR_VERSION_MISMATCH if the specified data was retrieved from a
  * different, incompatible version of OptiX. In this case, the state of \a acceleration is not changed.
  * 
  * If the call is successful, the dirty flag of \a acceleration will be cleared.
  * 
  * @param[in]   acceleration   The acceleration structure handle
  * @param[in]   data           Pointer to data containing the serialized state
  * @param[in]   size           The size in bytes of the buffer pointed to by \a data
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_VERSION_MISMATCH
  * 
  * <B>History</B>
  * 
  * @ref rtAccelerationSetData was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtAccelerationGetData,
  * @ref rtAccelerationGetDataSize
  * 
  */
  RTresult RTAPI rtAccelerationSetData(RTacceleration acceleration, const void* data, RTsize size);

  /**
  * @brief Marks an acceleration structure as dirty
  * 
  * @ingroup AccelerationStructure
  * 
  * <B>Description</B>
  * 
  * @ref rtAccelerationMarkDirty sets the dirty flag for \a acceleration.
  * 
  * Any acceleration structure which is marked dirty will be rebuilt on a call to one of
  * the @ref rtContextLaunch "rtContextLaunch" functions, and its dirty flag will be reset. The dirty flag will also
  * be reset on a sucessful call to @ref rtAccelerationSetData.
  * 
  * An acceleration structure which is not marked dirty will never be rebuilt, even if associated
  * groups, geometry, properties, or any other values have changed.
  * 
  * Initially after creation, acceleration structures are marked dirty.
  * 
  * @param[in]   acceleration   The acceleration structure handle
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtAccelerationMarkDirty was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtAccelerationIsDirty,
  * @ref rtAccelerationSetData,
  * @ref rtContextLaunch
  * 
  */
  RTresult RTAPI rtAccelerationMarkDirty(RTacceleration acceleration);
  
  /**
  * @brief Returns the dirty flag of an acceleration structure
  * 
  * @ingroup AccelerationStructure
  * 
  * <B>Description</B>
  * 
  * @ref rtAccelerationIsDirty returns whether the acceleration structure is currently marked dirty.
  * If the flag is set, a nonzero value will be returned in the location pointed to by \a dirty.
  * Otherwise, zero is returned.
  * 
  * Any acceleration structure which is marked dirty will be rebuilt on a call to one of
  * the @ref rtContextLaunch "rtContextLaunch" functions, and its dirty flag will be reset. The dirty flag will also
  * be reset on a sucessful call to @ref rtAccelerationSetData.
  * 
  * An acceleration structure which is not marked dirty will never be rebuilt, even if associated
  * groups, geometry, properties, or any other values have changed.
  * 
  * Initially after creation, acceleration structures are marked dirty.
  * 
  * @param[in]   acceleration   The acceleration structure handle
  * @param[out]  dirty          Returned dirty flag
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtAccelerationIsDirty was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtAccelerationMarkDirty,
  * @ref rtAccelerationSetData,
  * @ref rtContextLaunch
  * 
  */
  RTresult RTAPI rtAccelerationIsDirty(RTacceleration acceleration, int* dirty);

/************************************
 **
 **    GeometryInstance object
 **
 ***********************************/
 
  /**
  * @brief Creates a new geometry instance node
  * 
  * @ingroup GeometryInstance
  * 
  * <B>Description</B>
  * 
  * @ref rtGeometryInstanceCreate creates a new geometry instance node within a context. \a context
  * specifies the target context, and should be a value returned by
  * @ref rtContextCreate. After the call, \a *geometryinstance shall be set to the handle of
  * a newly created geometry instance node within \a context.
  * 
  * @param[in]   context            Specifies the rendering context of the GeometryInstance node
  * @param[out]  geometryinstance   New GeometryInstance node handle
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtGeometryInstanceCreate was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtGeometryInstanceDestroy,
  * @ref rtGeometryInstanceDestroy,
  * @ref rtGeometryInstanceGetContext
  * 
  */
  RTresult RTAPI rtGeometryInstanceCreate(RTcontext context, RTgeometryinstance* geometryinstance);
  
  /**
  * @brief Destroys a geometry instance node
  * 
  * @ingroup GeometryInstance
  * 
  * <B>Description</B>
  * 
  * @ref rtGeometryInstanceDestroy removes \a geometryinstance from its context and deletes it.
  * \a geometryinstance should be a value returned by @ref rtGeometryInstanceCreate.
  * Associated variables declared via @ref rtGeometryInstanceDeclareVariable are destroyed, but no child graph nodes are destroyed.
  * After the call, \a geometryinstance is no longer a valid handle.
  * 
  * @param[in]   geometryinstance   Handle of the geometry instance node to destroy
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtGeometryInstanceDestroy was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtGeometryInstanceCreate
  * 
  */
  RTresult RTAPI rtGeometryInstanceDestroy(RTgeometryinstance geometryinstance);
  
  /**
  * @brief Checks a GeometryInstance node for internal consistency
  * 
  * @ingroup GeometryInstance
  * 
  * <B>Description</B>
  * 
  * @ref rtGeometryInstanceValidate checks \a geometryinstance for completeness. If \a geomertryinstance or
  * any of the objects attached to \a geometry are not valid, the call will return
  * @ref RT_ERROR_INVALID_VALUE.
  * 
  * @param[in]   geometryinstance   GeometryInstance node of a model sub-tree to be validated
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtGeometryInstanceValidate was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtGeometryInstanceCreate
  * 
  */
  RTresult RTAPI rtGeometryInstanceValidate(RTgeometryinstance geometryinstance);
  
  /**
  * @brief Returns the context associated with a geometry instance node
  * 
  * @ingroup GeometryInstance
  * 
  * <B>Description</B>
  * 
  * @ref rtGeometryInstanceGetContext queries a geometry instance node for its associated context.
  * \a geometryinstance specifies the geometry node to query, and should be a value returned by
  * @ref rtGeometryInstanceCreate. After the call, \a *context shall be set to the context
  * associated with \a geometryinstance.
  * 
  * @param[in]   geometryinstance   Specifies the geometry instance
  * @param[out]  context            Handle for queried context
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtGeometryInstanceGetContext was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtGeometryInstanceGetContext
  * 
  */
  RTresult RTAPI rtGeometryInstanceGetContext(RTgeometryinstance geometryinstance, RTcontext* context);

  /**
  * @brief Attaches a Geometry node
  * 
  * @ingroup GeometryInstance
  * 
  * <B>Description</B>
  * 
  * @ref rtGeometryInstanceSetGeometry attaches a Geometry node to a GeometryInstance. 
  * Only \a one Geometry node can be attached to a GeometryInstance. However, it is 
  * at any time possible to attach a different Geometry node.
  * 
  * @param[in]   geometryinstance   GeometryInstance node handle to attach geometry
  * @param[in]   geometry           Geometry handle to attach to \a geometryinstance
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtGeometryInstanceSetGeometry was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtGeometryInstanceGetGeometry
  * 
  */
  RTresult RTAPI rtGeometryInstanceSetGeometry(RTgeometryinstance geometryinstance, RTgeometry  geometry);
  
  /**
  * @brief Returns the attached Geometry node
  * 
  * @ingroup GeometryInstance
  * 
  * <B>Description</B>
  * 
  * @ref rtGeometryInstanceGetGeometry sets \a geometry to the handle of the attached Geometry node. 
  * If no Geometry node is attached, @ref RT_ERROR_INVALID_VALUE is returned, else @ref RT_SUCCESS.
  * 
  * @param[in]   geometryinstance   GeometryInstance node handle to query geometry
  * @param[out]  geometry           Handle to attached Geometry node
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtGeometryInstanceGetGeometry was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtGeometryInstanceCreate,
  * @ref rtGeometryInstanceDestroy,
  * @ref rtGeometryInstanceValidate,
  * @ref rtGeometryInstanceSetGeometry
  * 
  */
  RTresult RTAPI rtGeometryInstanceGetGeometry(RTgeometryinstance geometryinstance, RTgeometry* geometry);

  /**
  * @brief Sets the number of materials
  * 
  * @ingroup GeometryInstance
  * 
  * <B>Description</B>
  * 
  * @ref rtGeometryInstanceSetMaterialCount sets the number of materials \a count that will be
  * attached to \a geometryinstance. The number of attached materials can be changed at any
  * time.  Increasing the number of materials will not modify already assigned materials.
  * Decreasing the number of materials will not modify the remaining already assigned
  * materials.
  * 
  * @param[in]   geometryinstance   GeometryInstance node to set number of materials
  * @param[in]   count              Number of materials to be set
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtGeometryInstanceSetMaterialCount was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtGeometryInstanceGetMaterialCount
  * 
  */
  RTresult RTAPI rtGeometryInstanceSetMaterialCount(RTgeometryinstance geometryinstance, unsigned int  count);
  
  /**
  * @brief Returns the number of attached materials
  * 
  * @ingroup GeometryInstance
  * 
  * <B>Description</B>
  * 
  * @ref rtGeometryInstanceGetMaterialCount returns for \a geometryinstance the number of attached Material nodes \a count. The number of materies can be set with @ref rtGeometryInstanceSetMaterialCount.
  * 
  * @param[in]   geometryinstance   GeometryInstance node to query from the number of materials
  * @param[out]  count              Number of attached materials
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtGeometryInstanceGetMaterialCount was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtGeometryInstanceSetMaterialCount
  * 
  */
  RTresult RTAPI rtGeometryInstanceGetMaterialCount(RTgeometryinstance geometryinstance, unsigned int* count);

  /**
  * @brief Sets a material
  * 
  * @ingroup GeometryInstance
  * 
  * <B>Description</B>
  * 
  * @ref rtGeometryInstanceSetMaterial attaches \a material to \a geometryinstance at position \a idx in its internal Material node list. 
  * \a idx has to be in the range \a 0 to @ref rtGeometryInstanceGetMaterialCount \a - 1.
  * 
  * @param[in]   geometryinstance   GeometryInstance node for which to set a material
  * @param[in]   idx                Index into the material list
  * @param[in]   material           Material handle to attach to \a geometryinstance
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtGeometryInstanceSetMaterial was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtGeometryInstanceGetMaterialCount,
  * @ref rtGeometryInstanceSetMaterialCount
  * 
  */
  RTresult RTAPI rtGeometryInstanceSetMaterial(RTgeometryinstance geometryinstance, unsigned int idx, RTmaterial  material);
  
  /**
  * @brief Returns a material handle
  * 
  * @ingroup GeometryInstance
  * 
  * <B>Description</B>
  * 
  * @ref rtGeometryInstanceGetMaterial returns handle \a material for the Material node at position \a idx 
  * in the material list of \a geometryinstance. \a idx must be in the range of \a 0 to @ref rtGeometryInstanceGetMaterialCount \a - 1.
  * 
  * @param[in]   geometryinstance   GeometryInstance node handle to query material
  * @param[in]   idx                Index of material
  * @param[out]  material           Handle to material
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtGeometryInstanceGetMaterial was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtGeometryInstanceGetMaterialCount,
  * @ref rtGeometryInstanceSetMaterial
  * 
  */
  RTresult RTAPI rtGeometryInstanceGetMaterial(RTgeometryinstance geometryinstance, unsigned int idx, RTmaterial* material);

  /**
  * @brief Declares a new named variable associated with a geometry node
  * 
  * @ingroup GeometryInstance
  * 
  * <B>Description</B>
  * 
  * @ref rtGeometryInstanceDeclareVariable declares a new variable associated with a
  * geometry instance node. \a geometryinstance specifies the target geometry node, and 
  * should be a value returned by @ref rtGeometryInstanceCreate. \a name specifies the 
  * name of the variable, and should be a \a NULL-terminated string. If there is 
  * currently no variable associated with \a geometryinstance named \a name, a new 
  * variable named \a name will be created and associated with \a geometryinstance. 
  * After the call, \a *v will be set to the handle of the newly-created variable. 
  * Otherwise, \a *v will be set to \a NULL. After declaration, the variable can be 
  * queried with @ref rtGeometryInstanceQueryVariable or @ref rtGeometryInstanceGetVariable. A declared 
  * variable does not have a type until its value is set with one of the 
  * @ref rtVariableSet functions. Once a variable is set, its type cannot be changed 
  * anymore.
  * 
  * @param[in]   geometryinstance   Specifies the associated GeometryInstance node
  * @param[in]   name               The name that identifies the variable
  * @param[out]  v                  Returns a handle to a newly declared variable
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtGeometryInstanceDeclareVariable was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref Variables,
  * @ref rtGeometryInstanceQueryVariable,
  * @ref rtGeometryInstanceGetVariable,
  * @ref rtGeometryInstanceRemoveVariable
  * 
  */
  RTresult RTAPI rtGeometryInstanceDeclareVariable(RTgeometryinstance geometryinstance, const char* name, RTvariable* v);
  
  /**
  * @brief Returns a handle to a named variable of a geometry node
  * 
  * @ingroup GeometryInstance
  * 
  * <B>Description</B>
  * 
  * @ref rtGeometryInstanceQueryVariable queries the handle of a geometry instance node's named variable.
  * \a geometryinstance specifies the target geometry node and should be a value returned
  * by @ref rtGeometryInstanceCreate. \a name specifies the name of the variable, and should
  * be a \a NULL-terminated string. If \a name is the name of a variable attached to
  * \a geometryinstance, \a *v will be a handle to that variable after the call.
  * Otherwise, \a *v will be \a NULL after the call. Geometry instance variables have to be declared 
  * with @ref rtGeometryInstanceDeclareVariable before they can be queried.
  * 
  * @param[in]   geometryinstance   The GeometryInstance node to query from a variable
  * @param[in]   name               The name that identifies the variable to be queried
  * @param[out]  v                  Returns the named variable
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtGeometryInstanceQueryVariable was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtGeometryInstanceDeclareVariable,
  * @ref rtGeometryInstanceRemoveVariable,
  * @ref rtGeometryInstanceGetVariableCount,
  * @ref rtGeometryInstanceGetVariable
  * 
  */
  RTresult RTAPI rtGeometryInstanceQueryVariable(RTgeometryinstance geometryinstance, const char* name, RTvariable* v);
  
  /**
  * @brief Removes a named variable from a geometry instance node
  * 
  * @ingroup GeometryInstance
  * 
  * <B>Description</B>
  * 
  * @ref rtGeometryInstanceRemoveVariable removes a named variable from a
  * geometry instance. The target geometry instance is specified by
  * \a geometryinstance, which should be a value returned by
  * @ref rtGeometryInstanceCreate. The variable to be removed is specified
  * by \a v, which should be a value returned by
  * @ref rtGeometryInstanceDeclareVariable. Once a variable has been removed
  * from this geometry instance, another variable with the same name as
  * the removed variable may be declared.
  * 
  * @param[in]   geometryinstance   The GeometryInstance node from which to remove a variable
  * @param[in]   v                  The variable to be removed
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * - @ref RT_ERROR_VARIABLE_NOT_FOUND
  * 
  * <B>History</B>
  * 
  * @ref rtGeometryInstanceRemoveVariable was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtContextRemoveVariable,
  * @ref rtGeometryInstanceDeclareVariable
  * 
  */
  RTresult RTAPI rtGeometryInstanceRemoveVariable(RTgeometryinstance geometryinstance, RTvariable v);
  
  /**
  * @brief Returns the number of attached variables
  * 
  * @ingroup GeometryInstance
  * 
  * <B>Description</B>
  * 
  * @ref rtGeometryInstanceGetVariableCount queries the number of variables attached to a geometry instance.
  * \a geometryinstance specifies the geometry instance, and should be a value returned by @ref rtGeometryInstanceCreate.
  * After the call, the number of variables attached to \a geometryinstance is returned to \a *count.
  * 
  * @param[in]   geometryinstance   The GeometryInstance node to query from the number of attached variables
  * @param[out]  count              Returns the number of attached variables
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtGeometryInstanceGetVariableCount was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtGeometryInstanceGetVariableCount,
  * @ref rtGeometryInstanceDeclareVariable,
  * @ref rtGeometryInstanceRemoveVariable
  * 
  */
  RTresult RTAPI rtGeometryInstanceGetVariableCount(RTgeometryinstance geometryinstance, unsigned int* count);
  
  /**
  * @brief Returns a handle to an indexed variable of a geometry instance node
  * 
  * @ingroup GeometryInstance
  * 
  * <B>Description</B>
  * 
  * @ref rtGeometryInstanceGetVariable queries the handle of a geometry instance's indexed variable.
  * \a geometryinstance specifies the target geometry instance and should be a value returned
  * by @ref rtGeometryInstanceCreate. \a index specifies the index of the variable, and
  * should be a value less than @ref rtGeometryInstanceGetVariableCount. If \a index is the
  * index of a variable attached to \a geometryinstance, \a *v will be a handle to that
  * variable after the call. Otherwise, \a *v will be \a NULL after the call. \a *v has to be
  *  declared first with @ref rtGeometryInstanceDeclareVariable before it can be queried.
  * 
  * @param[in]   geometryinstance   The GeometryInstance node from which to query a variable
  * @param[in]   index              The index that identifies the variable to be queried
  * @param[out]  v                  Returns handle to indexed variable
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * - @ref RT_ERROR_VARIABLE_NOT_FOUND
  * 
  * <B>History</B>
  * 
  * @ref rtGeometryInstanceGetVariable was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtGeometryDeclareVariable,
  * @ref rtGeometryGetVariableCount,
  * @ref rtGeometryRemoveVariable,
  * @ref rtGeometryQueryVariable
  * 
  */
  RTresult RTAPI rtGeometryInstanceGetVariable(RTgeometryinstance geometryinstance, unsigned int index, RTvariable* v);

/************************************
 **
 **    Geometry object
 **
 ***********************************/

  /**
  * @brief Creates a new geometry node
  * 
  * @ingroup Geometry
  * 
  * <B>Description</B>
  * 
  * @ref rtGeometryCreate creates a new geometry node within a context. \a context
  * specifies the target context, and should be a value returned by
  * @ref rtContextCreate.  After the call, \a *geometry shall be set to the handle of
  * a newly created geometry node within \a context.
  * 
  * @param[in]   context    Specifies the rendering context of the Geometry node
  * @param[out]  geometry   New Geometry node handle
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtGeometryCreate was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtGeometryDestroy,
  * @ref rtGeometrySetBoundingBoxProgram,
  * @ref rtGeometrySetIntersectionProgram
  * 
  */
  RTresult RTAPI rtGeometryCreate(RTcontext context, RTgeometry* geometry);
  
  /**
  * @brief Destroys a geometry node
  * 
  * @ingroup Geometry
  * 
  * <B>Description</B>
  * 
  * @ref rtGeometryDestroy removes \a geometry from its context and deletes it.
  * \a geometry should be a value returned by @ref rtGeometryCreate.
  * Associated variables declared via @ref rtGeometryDeclareVariable are destroyed, but no child graph nodes are destroyed.
  * After the call, \a geometry is no longer a valid handle.
  * 
  * @param[in]   geometry   Handle of the geometry node to destroy
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtGeometryDestroy was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtGeometryCreate,
  * @ref rtGeometrySetPrimitiveCount,
  * @ref rtGeometryGetPrimitiveCount
  * 
  */
  RTresult RTAPI rtGeometryDestroy(RTgeometry geometry);
  
  /**
  * @brief Validates the geometry nodes integrity
  * 
  * @ingroup Geometry
  * 
  * <B>Description</B>
  * 
  * @ref rtGeometryValidate checks \a geometry for completeness. If \a geomertry or
  * any of the objects attached to \a geometry are not valid, the call will return
  * @ref RT_ERROR_INVALID_VALUE.
  * 
  * @param[in]   geometry   The geometry node to be validated
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtGeometryValidate was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtContextValidate
  * 
  */
  RTresult RTAPI rtGeometryValidate(RTgeometry geometry);
  
  /**
  * @brief Returns the context associated with a geometry node
  * 
  * @ingroup Geometry
  * 
  * <B>Description</B>
  * 
  * @ref rtGeometryGetContext queries a geometry node for its associated context.
  * \a geometry specifies the geometry node to query, and should be a value returned by
  * @ref rtGeometryCreate. After the call, \a *context shall be set to the context
  * associated with \a geometry.
  * 
  * @param[in]   geometry   Specifies the geometry to query
  * @param[out]  context    The context associated with \a geometry
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtGeometryGetContext was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtGeometryCreate
  * 
  */
  RTresult RTAPI rtGeometryGetContext(RTgeometry geometry, RTcontext* context);

  /**
  * @brief Sets the number of primitives
  * 
  * @ingroup Geometry
  * 
  * <B>Description</B>
  * 
  * @ref rtGeometrySetPrimitiveCount sets the number of primitives \a num_primitives in \a geometry.
  * 
  * @param[in]   geometry         The geometry node for which to set the number of primitives
  * @param[in]   num_primitives   The number of primitives
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtGeometrySetPrimitiveCount was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtGeometryGetPrimitiveCount
  * 
  */
  RTresult RTAPI rtGeometrySetPrimitiveCount(RTgeometry geometry, unsigned int  num_primitives);
  
  /**
  * @brief Returns the number of primitives
  * 
  * @ingroup Geometry
  * 
  * <B>Description</B>
  * 
  * @ref rtGeometryGetPrimitiveCount returns for \a geometry the number of set primitives. The number of primitvies can be set with @ref rtGeometryGetPrimitiveCount.
  * 
  * @param[in]   geometry         Geometry node to query from the number of primitives
  * @param[out]  num_primitives   Number of primitives
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtGeometryGetPrimitiveCount was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtGeometrySetPrimitiveCount
  * 
  */
  RTresult RTAPI rtGeometryGetPrimitiveCount(RTgeometry geometry, unsigned int* num_primitives);

  /**
  * @brief Sets the primitive index offset
  * 
  * @ingroup Geometry
  * 
  * <B>Description</B>
  * 
  * @ref rtGeometrySetPrimitiveIndexOffset sets the primitive index offset
  * \a index_offset in \a geometry.  In the past, a @ref Geometry object's primitive
  * index range always started at zero (e.g., a Geometry with \a N primitives would
  * have a primitive index range of [0,N-1]).  The index offset is used to allow
  * @ref Geometry objects to have primitive index ranges starting at non-zero
  * positions (e.g., a Geometry with \a N primtives and and index offset of \a M
  * would have a primitive index range of [M,M+N-1]).  This feature enables the
  * sharing of vertex index buffers between multiple @ref Geometry objects.
  * 
  * @param[in]   geometry       The geometry node for which to set the primitive index offset
  * @param[in]   index_offset   The primitive index offset
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtGeometrySetPrimitiveIndexOffset was introduced in OptiX 3.5.
  * 
  * <B>See also</B>
  * @ref rtGeometryGetPrimitiveIndexOffset
  * 
  */
  RTresult RTAPI rtGeometrySetPrimitiveIndexOffset(RTgeometry geometry, unsigned int  index_offset);
  
  /**
  * @brief Returns the current primitive index offset
  * 
  * @ingroup Geometry
  * 
  * <B>Description</B>
  * 
  * @ref rtGeometryGetPrimitiveIndexOffset returns for \a geometry the primitive index offset. The primitive index offset can be set with @ref rtGeometrySetPrimitiveIndexOffset.
  * 
  * @param[in]   geometry       Geometry node to query for the primitive index offset
  * @param[out]  index_offset   Primitive index offset
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtGeometryGetPrimitiveIndexOffset was introduced in OptiX 3.5.
  * 
  * <B>See also</B>
  * @ref rtGeometrySetPrimitiveIndexOffset
  * 
  */
  RTresult RTAPI rtGeometryGetPrimitiveIndexOffset(RTgeometry geometry, unsigned int* index_offset);

  /**
  * @brief Sets the bounding box program
  * 
  * @ingroup Geometry
  * 
  * <B>Description</B>
  * 
  * @ref rtGeometrySetBoundingBoxProgram sets for \a geometry the \a program that computes an axis aligned bounding box 
  * for each attached primitive to \a geometry. RTprogram's can be either generated with @ref rtProgramCreateFromPTXFile or 
  * @ref rtProgramCreateFromPTXString. A bounding box program is mandatory for every geometry node.
  * 
  * @param[in]   geometry   The geometry node for which to set the bounding box program
  * @param[in]   program    Handle to the bounding box program
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * - @ref RT_ERROR_TYPE_MISMATCH
  * 
  * <B>History</B>
  * 
  * @ref rtGeometrySetBoundingBoxProgram was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtGeometryGetBoundingBoxProgram,
  * @ref rtProgramCreateFromPTXFile,
  * @ref rtProgramCreateFromPTXString
  * 
  */
  RTresult RTAPI rtGeometrySetBoundingBoxProgram(RTgeometry geometry, RTprogram  program);
  
  /**
  * @brief Returns the attached bounding box program
  * 
  * @ingroup Geometry
  * 
  * <B>Description</B>
  * 
  * @ref rtGeometryGetBoundingBoxProgram returns the handle \a program for
  * the attached bounding box program of \a geometry.
  * 
  * @param[in]   geometry   Geometry node handle from which to query program
  * @param[out]  program    Handle to attached bounding box program
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtGeometryGetBoundingBoxProgram was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtGeometrySetBoundingBoxProgram
  * 
  */
  RTresult RTAPI rtGeometryGetBoundingBoxProgram(RTgeometry geometry, RTprogram* program);

  /**
  * @brief Sets the intersection program
  * 
  * @ingroup Geometry
  * 
  * <B>Description</B>
  * 
  * @ref rtGeometrySetIntersectionProgram sets for \a geometry the \a program that performs ray primitive intersections. 
  * RTprogram's can be either generated with @ref rtProgramCreateFromPTXFile or @ref rtProgramCreateFromPTXString. An intersection 
  * program is mandatory for every geometry node.
  * 
  * @param[in]   geometry   The geometry node for which to set the intersection program
  * @param[in]   program    A handle to the ray primitive intersection program
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * - @ref RT_ERROR_TYPE_MISMATCH
  * 
  * <B>History</B>
  * 
  * @ref rtGeometrySetIntersectionProgram was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtGeometryGetIntersectionProgram,
  * @ref rtProgramCreateFromPTXFile,
  * @ref rtProgramCreateFromPTXString
  * 
  */
  RTresult RTAPI rtGeometrySetIntersectionProgram(RTgeometry geometry, RTprogram  program);
  
  /**
  * @brief Returns the attached intersection program
  * 
  * @ingroup Geometry
  * 
  * <B>Description</B>
  * 
  * @ref rtGeometryGetIntersectionProgram returns in \a program a handle of the attached intersection program.
  * 
  * @param[in]   geometry   Geometry node handle to query program
  * @param[out]  program    Handle to attached intersection program
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtGeometryGetIntersectionProgram was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtGeometrySetIntersectionProgram,
  * @ref rtProgramCreateFromPTXFile,
  * @ref rtProgramCreateFromPTXString
  * 
  */
  RTresult RTAPI rtGeometryGetIntersectionProgram(RTgeometry geometry, RTprogram* program);

  /**
  * @brief Sets the dirty flag
  * 
  * @ingroup Geometry
  * 
  * <B>Description</B>
  * 
  * @ref rtGeometryMarkDirty sets for \a geometry the dirty flag. By default
  * the dirty flag is set for a new Geometry node. After a call to
  * @ref rtContextLaunch "rtContextLaunch" the flag is automatically cleared.  When the dirty
  * flag is set, the geometry data is uploaded automatically to the device
  * while a @ref rtContextLaunch "rtContextLaunch" call.
  * 
  * @param[in]   geometry   The geometry node to mark as dirty
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtGeometryMarkDirty was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtGeometryIsDirty
  * 
  */
  RTresult RTAPI rtGeometryMarkDirty(RTgeometry geometry);
  
  /**
  * @brief Returns the dirty flag
  * 
  * @ingroup Geometry
  * 
  * <B>Description</B>
  * 
  * @ref rtGeometryIsDirty returns the dirty flag of \a geometry. The dirty
  * flag for geometry nodes can be set with @ref rtGeometryMarkDirty. By
  * default the flag is \a 1 for a new geometry node, indicating dirty.
  * After a call to @ref rtContextLaunch "rtContextLaunch" the flag is automatically set to
  * \a 0. When the dirty flag is set, the geometry data is uploaded
  * automatically to the device while a @ref rtContextLaunch "rtContextLaunch" call.
  * 
  * @param[in]   geometry   The geometry node to query from the dirty flag
  * @param[out]  dirty      Dirty flag
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtGeometryIsDirty was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtContextLaunch,
  * @ref rtGeometryMarkDirty
  * 
  */
  RTresult RTAPI rtGeometryIsDirty(RTgeometry geometry, int* dirty);

  /**
  * @brief Declares a new named variable associated with a geometry instance
  * 
  * @ingroup Geometry
  * 
  * <B>Description</B>
  * 
  * @ref rtGeometryDeclareVariable declares a new variable associated with a
  * geometry node. \a geometry specifies the target geometry node, and 
  * should be a value returned by @ref rtGeometryCreate. \a name specifies the 
  * name of the variable, and should be a \a NULL-terminated string. If there is 
  * currently no variable associated with \a geometry named \a name, a new 
  * variable named \a name will be created and associated with \a geometry. 
  * After the call, \a *v will be set to the handle of the newly-created variable. 
  * Otherwise, \a *v will be set to \a NULL. After declaration, the variable can be 
  * queried with @ref rtGeometryQueryVariable or @ref rtGeometryGetVariable. A declared 
  * variable does not have a type until its value is set with one of the 
  * @ref rtVariableSet functions. Once a variable is set, its type cannot be changed 
  * anymore.
  * 
  * @param[in]   geometry   Specifies the associated Geometry node
  * @param[in]   name       The name that identifies the variable
  * @param[out]  v          Returns a handle to a newly declared variable
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * - @ref RT_ERROR_VARIABLE_REDECLARED
  * - @ref RT_ERROR_ILLEGAL_SYMBOL
  * 
  * <B>History</B>
  * 
  * @ref rtGeometryDeclareVariable was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref Variables,
  * @ref rtGeometryQueryVariable,
  * @ref rtGeometryGetVariable,
  * @ref rtGeometryRemoveVariable
  * 
  */
  RTresult RTAPI rtGeometryDeclareVariable(RTgeometry geometry, const char* name, RTvariable* v);
  
  /**
  * @brief Returns a handle to a named variable of a geometry node
  * 
  * @ingroup Geometry
  * 
  * <B>Description</B>
  * 
  * @ref rtGeometryQueryVariable queries the handle of a geometry node's named variable.
  * \a geometry specifies the target geometry node and should be a value returned
  * by @ref rtGeometryCreate. \a name specifies the name of the variable, and should
  * be a \a NULL-terminated string. If \a name is the name of a variable attached to
  * \a geometry, \a *v will be a handle to that variable after the call.
  * Otherwise, \a *v will be \a NULL after the call. Geometry variables have to be declared 
  * with @ref rtGeometryDeclareVariable before they can be queried.
  * 
  * @param[in]   geometry   The geometry node to query from a variable
  * @param[in]   name       The name that identifies the variable to be queried
  * @param[out]  v          Returns the named variable
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * - @ref RT_ERROR_VARIABLE_NOT_FOUND
  * 
  * <B>History</B>
  * 
  * @ref rtGeometryQueryVariable was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtGeometryDeclareVariable,
  * @ref rtGeometryRemoveVariable,
  * @ref rtGeometryGetVariableCount,
  * @ref rtGeometryGetVariable
  * 
  */
  RTresult RTAPI rtGeometryQueryVariable(RTgeometry geometry, const char* name, RTvariable* v);
  
  /**
  * @brief Removes a named variable from a geometry node
  * 
  * @ingroup Geometry
  * 
  * <B>Description</B>
  * 
  * @ref rtGeometryRemoveVariable removes a named variable from a geometry node. The
  * target geometry is specified by \a geometry, which should be a value
  * returned by @ref rtGeometryCreate. The variable to remove is specified by
  * \a v, which should be a value returned by @ref rtGeometryDeclareVariable.
  * Once a variable has been removed from this geometry node, another variable with the
  * same name as the removed variable may be declared.
  * 
  * @param[in]   geometry   The geometry node from which to remove a variable
  * @param[in]   v          The variable to be removed
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * - @ref RT_ERROR_VARIABLE_NOT_FOUND
  * 
  * <B>History</B>
  * 
  * @ref rtGeometryRemoveVariable was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtContextRemoveVariable
  * 
  */
  RTresult RTAPI rtGeometryRemoveVariable(RTgeometry geometry, RTvariable v);
  
  /**
  * @brief Returns the number of attached variables
  * 
  * @ingroup Geometry
  * 
  * <B>Description</B>
  * 
  * @ref rtGeometryGetVariableCount queries the number of variables attached to a geometry node.
  * \a geometry specifies the geometry node, and should be a value returned by @ref rtGeometryCreate.
  * After the call, the number of variables attached to \a geometry is returned to \a *count.
  * 
  * @param[in]   geometry   The Geometry node to query from the number of attached variables
  * @param[out]  count      Returns the number of attached variables
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtGeometryGetVariableCount was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtGeometryGetVariableCount,
  * @ref rtGeometryDeclareVariable,
  * @ref rtGeometryRemoveVariable
  * 
  */
  RTresult RTAPI rtGeometryGetVariableCount(RTgeometry geometry, unsigned int* count);
  
  /**
  * @brief Returns a handle to an indexed variable of a geometry node
  * 
  * @ingroup Geometry
  * 
  * <B>Description</B>
  * 
  * @ref rtGeometryGetVariable queries the handle of a geometry node's indexed variable.
  * \a geometry specifies the target geometry and should be a value returned
  * by @ref rtGeometryCreate. \a index specifies the index of the variable, and
  * should be a value less than @ref rtGeometryGetVariableCount. If \a index is the
  * index of a variable attached to \a geometry, \a *v will be a handle to that
  * variable after the call. Otherwise, \a *v will be \a NULL after the call. \a *v has to be
  *  declared first with @ref rtGeometryDeclareVariable before it can be queried.
  * 
  * @param[in]   geometry   The geometry node from which to query a variable
  * @param[in]   index      The index that identifies the variable to be queried
  * @param[out]  v          Returns handle to indexed variable
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * - @ref RT_ERROR_VARIABLE_NOT_FOUND
  * 
  * <B>History</B>
  * 
  * @ref rtGeometryGetVariable was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtGeometryDeclareVariable,
  * @ref rtGeometryGetVariableCount,
  * @ref rtGeometryRemoveVariable,
  * @ref rtGeometryQueryVariable
  * 
  */
  RTresult RTAPI rtGeometryGetVariable(RTgeometry geometry, unsigned int index, RTvariable* v);

/************************************
 **
 **    Material object
 **
 ***********************************/

  /**
  * @brief Creates a new material
  * 
  * @ingroup Material
  * 
  * <B>Description</B>
  * 
  * @ref rtMaterialCreate creates a new material within a context. \a context
  * specifies the target context, and should be a value returned by
  * @ref rtContextCreate. After the call, if \a material is not \a NULL, \a *material
  * shall be set to the handle of a newly created material within \a context.
  * Otherwise, this call has no effect and returns @ref RT_ERROR_INVALID_VALUE.
  * 
  * @param[in]   context    Specifies a context within which to create a new material
  * @param[out]  material   Returns a newly created material
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtMaterialCreate was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtMaterialDestroy,
  * @ref rtContextCreate
  * 
  */
  RTresult RTAPI rtMaterialCreate(RTcontext context, RTmaterial* material);
  
  /**
  * @brief Destroys a material object
  * 
  * @ingroup Material
  * 
  * <B>Description</B>
  * 
  * @ref rtMaterialDestroy removes \a material from its context and deletes it.
  * \a material should be a value returned by @ref rtMaterialCreate.
  * Associated variables declared via @ref rtMaterialDeclareVariable are destroyed, but no child graph nodes are destroyed.
  * After the call, \a material is no longer a valid handle.
  * 
  * @param[in]   material   Handle of the material node to destroy
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtMaterialDestroy was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtMaterialCreate
  * 
  */
  RTresult RTAPI rtMaterialDestroy(RTmaterial material);
  
  /**
  * @brief Verifies the state of a material
  * 
  * @ingroup Material
  * 
  * <B>Description</B>
  * 
  * @ref rtMaterialValidate checks \a material for completeness. If \a material or
  * any of the objects attached to \a material are not valid, the call will return
  * @ref RT_ERROR_INVALID_VALUE.
  * 
  * @param[in]   material   Specifies the material to be validated
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtMaterialValidate was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtMaterialCreate
  * 
  */
  RTresult RTAPI rtMaterialValidate(RTmaterial material);
  
  /**
  * @brief Returns the context associated with a material
  * 
  * @ingroup Material
  * 
  * <B>Description</B>
  * 
  * @ref rtMaterialGetContext queries a material for its associated context.
  * \a material specifies the material to query, and should be a value returned by
  * @ref rtMaterialCreate. After the call, if both parameters are valid, \a *context
  * shall be set to the context associated with \a material. Otherwise, the call
  * has no effect and returns @ref RT_ERROR_INVALID_VALUE.
  * 
  * @param[in]   material   Specifies the material to query
  * @param[out]  context    Returns the context associated with the material
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtMaterialGetContext was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtMaterialCreate
  * 
  */
  RTresult RTAPI rtMaterialGetContext(RTmaterial material, RTcontext* context);

  /**
  * @brief Sets the closest hit program associated with a (material, ray type) tuple
  * 
  * @ingroup Material
  * 
  * <B>Description</B>
  * 
  * @ref rtMaterialSetClosestHitProgram specifies a closest hit program to associate
  * with a (material, ray type) tuple. \a material specifies the material of
  * interest and should be a value returned by @ref rtMaterialCreate.
  * \a ray_type_index specifies the type of ray to which the program applies and
  * should be a value less than the value returned by @ref rtContextGetRayTypeCount.
  * \a program specifies the target closest hit program which shall apply to
  * the tuple (\a material, \a ray_type_index) and should be a value returned by
  * either @ref rtProgramCreateFromPTXString or @ref rtProgramCreateFromPTXFile.
  * 
  * @param[in]   material         Specifies the material of the (material, ray type) tuple to modify
  * @param[in]   ray_type_index   Specifies the ray type of the (material, ray type) tuple to modify
  * @param[in]   program          Specifies the closest hit program to associate with the (material, ray type) tuple
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * - @ref RT_ERROR_TYPE_MISMATCH
  * 
  * <B>History</B>
  * 
  * @ref rtMaterialSetClosestHitProgram was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtMaterialGetClosestHitProgram,
  * @ref rtMaterialCreate,
  * @ref rtContextGetRayTypeCount,
  * @ref rtProgramCreateFromPTXString,
  * @ref rtProgramCreateFromPTXFile
  * 
  */
  RTresult RTAPI rtMaterialSetClosestHitProgram(RTmaterial material, unsigned int ray_type_index, RTprogram  program);
  
  /**
  * @brief Returns the closest hit program associated with a (material, ray type) tuple
  * 
  * @ingroup Material
  * 
  * <B>Description</B>
  * 
  * @ref rtMaterialGetClosestHitProgram queries the closest hit program associated
  * with a (material, ray type) tuple. \a material specifies the material of
  * interest and should be a value returned by @ref rtMaterialCreate.
  * \a ray_type_index specifies the target ray type and should be a value
  * less than the value returned by @ref rtContextGetRayTypeCount. After the call,
  * if all parameters are valid, \a *program shall be set to the handle of the
  * any hit program associated with the tuple (\a material, \a ray_type_index).
  * Otherwise, the call has no effect and returns @ref RT_ERROR_INVALID_VALUE.
  * 
  * @param[in]   material         Specifies the material of the (material, ray type) tuple to query
  * @param[in]   ray_type_index   Specifies the type of ray of the (material, ray type) tuple to query
  * @param[out]  program          Returns the closest hit program associated with the (material, ray type) tuple
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtMaterialGetClosestHitProgram was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtMaterialSetClosestHitProgram,
  * @ref rtMaterialCreate,
  * @ref rtContextGetRayTypeCount
  * 
  */
  RTresult RTAPI rtMaterialGetClosestHitProgram(RTmaterial material, unsigned int ray_type_index, RTprogram* program);

  /**
  * @brief Sets the any hit program associated with a (material, ray type) tuple
  * 
  * @ingroup Material
  * 
  * <B>Description</B>
  * 
  * @ref rtMaterialSetAnyHitProgram specifies an any hit program to associate with a
  * (material, ray type) tuple. \a material specifies the target material and
  * should be a value returned by @ref rtMaterialCreate. \a ray_type_index specifies
  * the type of ray to which the program applies and should be a value less than
  * the value returned by @ref rtContextGetRayTypeCount. \a program specifies the
  * target any hit program which shall apply to the tuple (\a material,
  * \a ray_type_index) and should be a value returned by either
  * @ref rtProgramCreateFromPTXString or @ref rtProgramCreateFromPTXFile.
  * 
  * @param[in]   material         Specifies the material of the (material, ray type) tuple to modify
  * @param[in]   ray_type_index   Specifies the type of ray of the (material, ray type) tuple to modify
  * @param[in]   program          Specifies the any hit program to associate with the (material, ray type) tuple
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * - @ref RT_ERROR_TYPE_MISMATCH
  * 
  * <B>History</B>
  * 
  * @ref rtMaterialSetAnyHitProgram was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtMaterialGetAnyHitProgram,
  * @ref rtMaterialCreate,
  * @ref rtContextGetRayTypeCount,
  * @ref rtProgramCreateFromPTXString,
  * @ref rtProgramCreateFromPTXFile
  * 
  */
  RTresult RTAPI rtMaterialSetAnyHitProgram(RTmaterial material, unsigned int ray_type_index, RTprogram  program);
  
  /**
  * @brief Returns the any hit program associated with a (material, ray type) tuple
  * 
  * @ingroup Material
  * 
  * <B>Description</B>
  * 
  * @ref rtMaterialGetAnyHitProgram queries the any hit program associated
  * with a (material, ray type) tuple. \a material specifies the material of
  * interest and should be a value returned by @ref rtMaterialCreate.
  * \a ray_type_index specifies the target ray type and should be a value
  * less than the value returned by @ref rtContextGetRayTypeCount. After the call,
  * if all parameters are valid, \a *program shall be set to the handle of the
  * any hit program associated with the tuple (\a material, \a ray_type_index).
  * Otherwise, the call has no effect and returns @ref RT_ERROR_INVALID_VALUE.
  * 
  * @param[in]   material         Specifies the material of the (material, ray type) tuple to query
  * @param[in]   ray_type_index   Specifies the type of ray of the (material, ray type) tuple to query
  * @param[out]  program          Returns the any hit program associated with the (material, ray type) tuple
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtMaterialGetAnyHitProgram was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtMaterialSetAnyHitProgram,
  * @ref rtMaterialCreate,
  * @ref rtContextGetRayTypeCount
  * 
  */
  RTresult RTAPI rtMaterialGetAnyHitProgram(RTmaterial material, unsigned int ray_type_index, RTprogram* program);

  /**
  * @brief Declares a new named variable to be associated with a material
  * 
  * @ingroup Material
  * 
  * <B>Description</B>
  * 
  * @ref rtMaterialDeclareVariable declares a new variable to be associated with a
  * material. \a material specifies the target material, and should be a value
  * returned by @ref rtMaterialCreate. \a name specifies the name of the variable,
  * and should be a \a NULL-terminated string. If there is currently no
  * variable associated with \a material named \a name, and \a variable is
  * not \a NULL, a new variable named \a name will be created and associated
  * with \a material. After the call, \a *variable shall be set to the
  * handle of the newly-created variable. Otherwise, this call has no
  * effect and shall return either @ref RT_ERROR_INVALID_VALUE if either
  * \a name or \a variable is equal to \a NULL or
  * @ref RT_ERROR_VARIABLE_REDECLARED if \a name is the name of an existing
  * variable associated with the material.
  * 
  * @param[in]   material   Specifies the material to modify
  * @param[in]   name       Specifies the name of the variable
  * @param[out]  v          Returns a handle to a newly declared variable
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * - @ref RT_ERROR_VARIABLE_REDECLARED
  * - @ref RT_ERROR_ILLEGAL_SYMBOL
  * 
  * <B>History</B>
  * 
  * @ref rtMaterialDeclareVariable was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtMaterialGetVariable,
  * @ref rtMaterialQueryVariable,
  * @ref rtMaterialCreate
  * 
  */
  RTresult RTAPI rtMaterialDeclareVariable(RTmaterial material, const char* name, RTvariable* v);
  
  /**
  * @brief Queries for the existence of a named variable of a material
  * 
  * @ingroup Material
  * 
  * <B>Description</B>
  * 
  * @ref rtMaterialQueryVariable queries for the existence of a material's named
  * variable. \a material specifies the target material and should be a value
  * returned by @ref rtMaterialCreate. \a name specifies the name of the variable,
  * and should be a \a NULL-terminated string. If \a material is a valid
  * material and \a name is the name of a variable attached to
  * \a material, \a *variable shall be set to a handle to that variable
  * after the call. Otherwise, \a *variable shall be set to \a NULL. If
  * \a material is not a valid material, @ref RT_ERROR_INVALID_VALUE shall
  * be returned.
  * 
  * @param[in]   material   Specifies the material to query
  * @param[in]   name       Specifies the name of the variable to query
  * @param[out]  v          Returns a the named variable, if it exists
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtMaterialQueryVariable was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtMaterialGetVariable,
  * @ref rtMaterialCreate
  * 
  */
  RTresult RTAPI rtMaterialQueryVariable(RTmaterial material, const char* name, RTvariable* v);
  
  /**
  * @brief Removes a variable from a material
  * 
  * @ingroup Material
  * 
  * <B>Description</B>
  * 
  * @ref rtMaterialRemoveVariable removes a variable from a material. The material of
  * interest is specified by \a material, which should be a value returned by
  * @ref rtMaterialCreate. The variable to remove is specified by \a variable, which
  * should be a value returned by @ref rtMaterialDeclareVariable. Once a variable
  * has been removed from this material, another variable with the same name as the
  * removed variable may be declared. If \a material does not refer to a valid material,
  * this call has no effect and returns @ref RT_ERROR_INVALID_VALUE. If \a variable is not
  * a valid variable or does not belong to \a material, this call has no effect and
  * returns @ref RT_ERROR_INVALID_VALUE or @ref RT_ERROR_VARIABLE_NOT_FOUND, respectively.
  * 
  * @param[in]   material   Specifies the material to modify
  * @param[in]   v          Specifies the variable to remove
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * - @ref RT_ERROR_VARIABLE_NOT_FOUND
  * 
  * <B>History</B>
  * 
  * @ref rtMaterialRemoveVariable was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtMaterialDeclareVariable,
  * @ref rtMaterialCreate
  * 
  */
  RTresult RTAPI rtMaterialRemoveVariable(RTmaterial material, RTvariable v);
  
  /**
  * @brief Returns the number of variables attached to a material
  * 
  * @ingroup Material
  * 
  * <B>Description</B>
  * 
  * @ref rtMaterialGetVariableCount queries the number of variables attached to a
  * material. \a material specifies the material, and should be a value returned by
  * @ref rtMaterialCreate. After the call, if both parameters are valid, the number
  * of variables attached to \a material is returned to \a *count. Otherwise, the
  * call has no effect and returns @ref RT_ERROR_INVALID_VALUE.
  * 
  * @param[in]   material   Specifies the material to query
  * @param[out]  count      Returns the number of variables
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtMaterialGetVariableCount was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtMaterialCreate
  * 
  */
  RTresult RTAPI rtMaterialGetVariableCount(RTmaterial material, unsigned int* count);
  
  /**
  * @brief Returns a handle to an indexed variable of a material
  * 
  * @ingroup Material
  * 
  * <B>Description</B>
  * 
  * @ref rtMaterialGetVariable queries the handle of a material's indexed variable.
  * \a material specifies the target material and should be a value returned
  * by @ref rtMaterialCreate. \a index specifies the index of the variable, and
  * should be a value less than @ref rtMaterialGetVariableCount. If \a material is a
  * valid material and \a index is the index of a variable attached to \a material,
  * \a *variable shall be set to a handle to that variable after the call. Otherwise,
  * \a *variable shall be set to \a NULL and either @ref RT_ERROR_INVALID_VALUE
  * or @ref RT_ERROR_VARIABLE_NOT_FOUND shall be returned depending on the
  * validity of \a material, or \a index, respectively.
  * 
  * @param[in]   material   Specifies the material to query
  * @param[in]   index      Specifies the index of the variable to query
  * @param[out]  v          Returns the indexed variable
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_VARIABLE_NOT_FOUND
  * 
  * <B>History</B>
  * 
  * @ref rtMaterialGetVariable was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtMaterialQueryVariable,
  * @ref rtMaterialGetVariableCount,
  * @ref rtMaterialCreate
  * 
  */
  RTresult RTAPI rtMaterialGetVariable(RTmaterial material, unsigned int index, RTvariable* v);

/************************************
 **
 **    TextureSampler object
 **
 ***********************************/
  
  /**
  * @brief Creates a new texture sampler object
  * 
  * @ingroup TextureSampler
  * 
  * <B>Description</B>
  * 
  * @ref rtTextureSamplerCreate allocates and returns a new handle to a texture sampler object, in \a *texturesampler, and
  * associates it with \a context.
  * 
  * @param[in]   context          The context the texture sampler object will be created in
  * @param[out]  texturesampler   The return handle to the new texture sampler object
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtTextureSamplerCreate was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtTextureSamplerDestroy
  * 
  */
  RTresult RTAPI rtTextureSamplerCreate(RTcontext context, RTtexturesampler* texturesampler);
  
  /**
  * @brief Destroys a texture sampler object
  * 
  * @ingroup TextureSampler
  * 
  * <B>Description</B>
  * 
  * @ref rtTextureSamplerDestroy removes \a texturesampler from its context and deletes it.
  * \a texturesampler should be a value returned by @ref rtTextureSamplerCreate.
  * After the call, \a texturesampler is no longer a valid handle.
  * Any API object that referenced \a texturesampler will have its reference invalidated.
  * 
  * @param[in]   texturesampler   Handle of the texture sampler to destroy
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtTextureSamplerDestroy was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtTextureSamplerCreate
  * 
  */
  RTresult RTAPI rtTextureSamplerDestroy(RTtexturesampler texturesampler);
  
  /**
  * @brief Validates the state of a texture sampler
  * 
  * @ingroup TextureSampler
  * 
  * <B>Description</B>
  * 
  * @ref rtTextureSamplerValidate checks \a texturesampler for completeness.  If \a texturesampler does not have buffers
  * attached to all of its MIP levels and array slices or if the filtering modes are incompatible with the current
  * MIP level and array slice configuration then the call will return @ref RT_ERROR_INVALID_CONTEXT.
  * 
  * @param[in]   texturesampler   The texture sampler to be validated
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtTextureSamplerValidate was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtContextValidate
  * 
  */
  RTresult RTAPI rtTextureSamplerValidate(RTtexturesampler texturesampler);
  
  /**
  * @brief Gets the context object that created this texture sampler
  * 
  * @ingroup TextureSampler
  * 
  * <B>Description</B>
  * 
  * @ref rtTextureSamplerGetContext returns a handle to the context object that was used to create
  * \a texturesampler.  If \a context is \a NULL, the call will return @ref RT_ERROR_INVALID_VALUE.
  * 
  * @param[in]   texturesampler   The texture sampler object to be queried for its context
  * @param[out]  context          The return handle for the context object of the texture sampler
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtTextureSamplerGetContext was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtContextCreate
  * 
  */
  RTresult RTAPI rtTextureSamplerGetContext(RTtexturesampler texturesampler, RTcontext* context);

  /**
  * @brief Sets the number of MIP levels in a texture sampler
  * 
  * @ingroup TextureSampler
  * 
  * <B>Description</B>
  * 
  * @ref rtTextureSamplerSetMipLevelCount sets the number of MIP levels in \a texturesampler to \a num_mip_levels.
  * 
  * @param[in]   texturesampler   The texture sampler object to be changed
  * @param[in]   num_mip_levels   The new number of MIP levels of the texture sampler
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtTextureSamplerSetMipLevelCount was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtTextureSamplerGetMipLevelCount
  * 
  */
  RTresult RTAPI rtTextureSamplerSetMipLevelCount(RTtexturesampler texturesampler, unsigned int  num_mip_levels);
  
  /**
  * @brief Gets the number of MIP levels in a texture sampler
  * 
  * @ingroup TextureSampler
  * 
  * <B>Description</B>
  * 
  * @ref rtTextureSamplerGetMipLevelCount gets the number of MIP levels contained in \a texturesampler and stores it in
  * \a *num_mip_levels.
  * 
  * @param[in]   texturesampler   The texture sampler object to be queried
  * @param[out]  num_mip_levels   The return handle for the number of MIP levels in the texture sampler
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtTextureSamplerGetMipLevelCount was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtTextureSamplerSetMipLevelCount
  * 
  */
  RTresult RTAPI rtTextureSamplerGetMipLevelCount(RTtexturesampler texturesampler, unsigned int* num_mip_levels);

  /**
  * @brief Sets the array size of a texture sampler
  * 
  * @ingroup TextureSampler
  * 
  * <B>Description</B>
  * 
  * @ref rtTextureSamplerSetArraySize specifies the number of texture array slices present in \a texturesampler as
  * \a num_textures_in_array.  After changing the number of slices in the array, buffers must be reassociated with
  * \a texturesampler via @ref rtTextureSamplerSetBuffer.
  * 
  * @param[in]   texturesampler                The texture sampler object to be changed
  * @param[in]   num_textures_in_array         The new number of array slices of the texture sampler
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtTextureSamplerSetArraySize was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtTextureSamplerGetArraySize
  * 
  */
  RTresult RTAPI rtTextureSamplerSetArraySize(RTtexturesampler texturesampler, unsigned int  num_textures_in_array);
  
  /**
  * @brief Gets the number of array slices present in a texture sampler
  * 
  * @ingroup TextureSampler
  * 
  * <B>Description</B>
  * 
  * @ref rtTextureSamplerGetArraySize gets the number of texture array slices in \a texturesampler and stores it in
  * \a *num_textures_in_array.
  * 
  * @param[in]   texturesampler          The texture sampler object to be queried
  * @param[out]  num_textures_in_array   The return handle for the number of texture slices the texture sampler
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtTextureSamplerGetArraySize was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtTextureSamplerSetArraySize
  * 
  */
  RTresult RTAPI rtTextureSamplerGetArraySize(RTtexturesampler texturesampler, unsigned int* num_textures_in_array);

  /**
  * @brief Sets the wrapping mode of a texture sampler
  * 
  * @ingroup TextureSampler
  * 
  * <B>Description</B>
  * 
  * @ref rtTextureSamplerSetWrapMode sets the wrapping mode of
  * \a texturesampler to \a wrapmode for the texture dimension specified
  * by \a dimension.  \a wrapmode can take one of the following values:
  * 
  *  - @ref RT_WRAP_REPEAT
  *  - @ref RT_WRAP_CLAMP_TO_EDGE
  *  - @ref RT_WRAP_MIRROR
  *  - @ref RT_WRAP_CLAMP_TO_BORDER
  * 
  * The wrapping mode controls the behavior of the texture sampler as
  * texture coordinates wrap around the range specified by the indexing
  * mode.  These values mirror the CUDA behavior of textures. 
  * See CUDA programming guide for details.
  * 
  * @param[in]   texturesampler   The texture sampler object to be changed
  * @param[in]   dimension        Dimension of the texture
  * @param[in]   wrapmode         The new wrap mode of the texture sampler
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtTextureSamplerSetWrapMode was introduced in OptiX 1.0.
  * @ref RT_WRAP_MIRROR and @ref RT_WRAP_CLAMP_TO_BORDER were introduced in OptiX 3.0.
  * 
  * <B>See also</B>
  * @ref rtTextureSamplerGetWrapMode
  * 
  */
  RTresult RTAPI rtTextureSamplerSetWrapMode(RTtexturesampler texturesampler, unsigned int dimension, RTwrapmode wrapmode);
  
  /**
  * @brief Gets the wrap mode of a texture sampler
  * 
  * @ingroup TextureSampler
  * 
  * <B>Description</B>
  * 
  * @ref rtTextureSamplerGetWrapMode gets the texture wrapping mode of \a texturesampler and stores it in \a *wrapmode.
  * See @ref rtTextureSamplerSetWrapMode for a list of values @ref RTwrapmode can take.
  * 
  * @param[in]   texturesampler   The texture sampler object to be queried
  * @param[in]   dimension        Dimension for the wrapping
  * @param[out]  wrapmode         The return handle for the wrap mode of the texture sampler
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtTextureSamplerGetWrapMode was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtTextureSamplerSetWrapMode
  * 
  */
  RTresult RTAPI rtTextureSamplerGetWrapMode(RTtexturesampler texturesampler, unsigned int dimension, RTwrapmode* wrapmode);

  /**
  * @brief Sets the filtering modes of a texture sampler
  * 
  * @ingroup TextureSampler
  * 
  * <B>Description</B>
  * 
  * @ref rtTextureSamplerSetFilteringModes sets the minification, magnification and MIP mapping filter modes for \a texturesampler.
  * RTfiltermode must be one of the following values:
  * 
  *  - @ref RT_FILTER_NEAREST
  *  - @ref RT_FILTER_LINEAR
  *  - @ref RT_FILTER_NONE
  * 
  * These filter modes specify how the texture sampler will interpolate
  * buffer data that has been attached to it.  \a minification and
  * \a magnification must be one of @ref RT_FILTER_NEAREST or
  * @ref RT_FILTER_LINEAR.  \a mipmapping may be any of the three values but
  * must be @ref RT_FILTER_NONE if the texture sampler contains only a
  * single MIP level or one of @ref RT_FILTER_NEAREST or @ref RT_FILTER_LINEAR
  * if the texture sampler contains more than one MIP level.
  * 
  * @param[in]   texturesampler   The texture sampler object to be changed
  * @param[in]   minification     The new minification filter mode of the texture sampler
  * @param[in]   magnification    The new magnification filter mode of the texture sampler
  * @param[in]   mipmapping       The new MIP mapping filter mode of the texture sampler
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtTextureSamplerSetFilteringModes was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtTextureSamplerGetFilteringModes
  * 
  */
  RTresult RTAPI rtTextureSamplerSetFilteringModes(RTtexturesampler texturesampler, RTfiltermode  minification, RTfiltermode  magnification, RTfiltermode  mipmapping);
  
  /**
  * @brief Gets the filtering modes of a texture sampler
  * 
  * @ingroup TextureSampler
  * 
  * <B>Description</B>
  * 
  * @ref rtTextureSamplerGetFilteringModes gets the minification, magnification and MIP mapping filtering modes from
  * \a texturesampler and stores them in \a *minification, \a *magnification and \a *mipmapping, respectively.  See
  * @ref rtTextureSamplerSetFilteringModes for the values @ref RTfiltermode may take.
  * 
  * @param[in]   texturesampler   The texture sampler object to be queried
  * @param[out]  minification     The return handle for the minification filtering mode of the texture sampler
  * @param[out]  magnification    The return handle for the magnification filtering mode of the texture sampler
  * @param[out]  mipmapping       The return handle for the MIP mapping filtering mode of the texture sampler
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtTextureSamplerGetFilteringModes was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtTextureSamplerSetFilteringModes
  * 
  */
  RTresult RTAPI rtTextureSamplerGetFilteringModes(RTtexturesampler texturesampler, RTfiltermode* minification, RTfiltermode* magnification, RTfiltermode* mipmapping);

  /**
  * @brief Sets the maximum anisotropy of a texture sampler
  * 
  * @ingroup TextureSampler
  * 
  * <B>Description</B>
  * 
  * @ref rtTextureSamplerSetMaxAnisotropy sets the maximum anisotropy of \a texturesampler to \a value.  A float
  * value greater than 0 will enable anisotropic filtering at the specified value.
  * 
  * @param[in]   texturesampler   The texture sampler object to be changed
  * @param[in]   value            The new maximum anisotropy level of the texture sampler
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtTextureSamplerSetMaxAnisotropy was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtTextureSamplerGetMaxAnisotropy
  * 
  */
  RTresult RTAPI rtTextureSamplerSetMaxAnisotropy(RTtexturesampler texturesampler, float value);
  
  /**
  * @brief Gets the maximum anisotropy level for a texture sampler
  * 
  * @ingroup TextureSampler
  * 
  * <B>Description</B>
  * 
  * @ref rtTextureSamplerGetMaxAnisotropy gets the maximum anisotropy level for \a texturesampler and stores
  * it in \a *value.
  * 
  * @param[in]   texturesampler   The texture sampler object to be queried
  * @param[out]  value            The return handle for the maximum anisotropy level of the texture sampler
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtTextureSamplerGetMaxAnisotropy was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtTextureSamplerSetMaxAnisotropy
  * 
  */
  RTresult RTAPI rtTextureSamplerGetMaxAnisotropy(RTtexturesampler texturesampler, float* value);

  /**
  * @brief Sets the read mode of a texture sampler
  * 
  * @ingroup TextureSampler
  * 
  * <B>Description</B>
  * 
  * @ref rtTextureSamplerSetReadMode sets the data read mode of \a texturesampler to \a readmode.
  * \a readmode can take one of the following values:
  * 
  *  - @ref RT_TEXTURE_READ_ELEMENT_TYPE
  *  - @ref RT_TEXTURE_READ_NORMALIZED_FLOAT
  * 
  * \a readmode controls the returned value of the texture sampler when it is used to sample
  * textures.  @ref RT_TEXTURE_READ_ELEMENT_TYPE will return data of the type of the underlying
  * buffer objects.  @ref RT_TEXTURE_READ_NORMALIZED_FLOAT will return floating point values
  * normalized by the range of the underlying type.  If the underlying type is floating point,
  * @ref RT_TEXTURE_READ_NORMALIZED_FLOAT and @ref RT_TEXTURE_READ_ELEMENT_TYPE are equivalent,
  * always returning the unmodified floating point value.
  * 
  * For example, a texture sampler that samples a buffer of type @ref RT_FORMAT_UNSIGNED_BYTE with
  * a read mode of @ref RT_TEXTURE_READ_NORMALIZED_FLOAT will convert integral values from the
  * range [0,255] to floating point values in the range [0,1] automatically as the buffer is
  * sampled from.
  * 
  * @param[in]   texturesampler   The texture sampler object to be changed
  * @param[in]   readmode         The new read mode of the texture sampler
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtTextureSamplerSetReadMode was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtTextureSamplerGetReadMode
  * 
  */
  RTresult RTAPI rtTextureSamplerSetReadMode(RTtexturesampler texturesampler, RTtexturereadmode  readmode);
  
  /**
  * @brief Gets the read mode of a texture sampler
  * 
  * @ingroup TextureSampler
  * 
  * <B>Description</B>
  * 
  * @ref rtTextureSamplerGetReadMode gets the read mode of \a texturesampler and stores it in \a *readmode.
  * See @ref rtTextureSamplerSetReadMode for a list of values @ref RTtexturereadmode can take.
  * 
  * @param[in]   texturesampler   The texture sampler object to be queried
  * @param[out]  readmode         The return handle for the read mode of the texture sampler
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtTextureSamplerGetReadMode was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtTextureSamplerSetReadMode
  * 
  */
  RTresult RTAPI rtTextureSamplerGetReadMode(RTtexturesampler texturesampler, RTtexturereadmode* readmode);

  /**
  * @brief Sets whether texture coordinates for this texture sampler are normalized
  * 
  * @ingroup TextureSampler
  * 
  * <B>Description</B>
  * 
  * @ref rtTextureSamplerSetIndexingMode sets the indexing mode of \a texturesampler to \a indexmode.  \a indexmode
  * can take on one of the following values:
  * 
  *  - @ref RT_TEXTURE_INDEX_NORMALIZED_COORDINATES,
  *  - @ref RT_TEXTURE_INDEX_ARRAY_INDEX
  * 
  * These values are used to control the interpretation of texture coordinates.  If the index mode is set to
  * @ref RT_TEXTURE_INDEX_NORMALIZED_COORDINATES, the texture is parameterized over [0,1].  If the index
  * mode is set to @ref RT_TEXTURE_INDEX_ARRAY_INDEX then texture coordinates are interpreted as array indices
  * into the contents of the underlying buffer objects.
  * 
  * @param[in]   texturesampler   The texture sampler object to be changed
  * @param[in]   indexmode        The new indexing mode of the texture sampler
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtTextureSamplerSetIndexingMode was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtTextureSamplerGetIndexingMode
  * 
  */
  RTresult RTAPI rtTextureSamplerSetIndexingMode(RTtexturesampler texturesampler, RTtextureindexmode  indexmode);
  
  /**
  * @brief Gets the indexing mode of a texture sampler
  * 
  * @ingroup TextureSampler
  * 
  * <B>Description</B>
  * 
  * @ref rtTextureSamplerGetIndexingMode gets the indexing mode of \a texturesampler and stores it in \a *indexmode.
  * See @ref rtTextureSamplerSetIndexingMode for the values @ref RTtextureindexmode may take.
  * 
  * @param[in]   texturesampler   The texture sampler object to be queried
  * @param[out]  indexmode        The return handle for the indexing mode of the texture sampler
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtTextureSamplerGetIndexingMode was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtTextureSamplerSetIndexingMode
  * 
  */
  RTresult RTAPI rtTextureSamplerGetIndexingMode(RTtexturesampler texturesampler, RTtextureindexmode* indexmode);

  /**
  * @brief Attaches a buffer object to a texture sampler
  * 
  * @ingroup TextureSampler
  * 
  * <B>Description</B>
  * 
  * @ref rtTextureSamplerSetBuffer attaches \a buffer to \a texturesampler at the specified array slice and MIP level.
  * The array slice and MIP level are specified by \a texture_array_idx and \a mip_level, respectively.
  * 
  * @param[in]   texturesampler      The texture sampler object that will contain the buffer
  * @param[in]   texture_array_idx   The array slice index the buffer will be attached to
  * @param[in]   mip_level           The MIP level the buffer will be attached to
  * @param[in]   buffer              The buffer to be attached to the texture sampler
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtTextureSamplerSetBuffer was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtTextureSamplerGetBuffer
  * 
  */
  RTresult RTAPI rtTextureSamplerSetBuffer(RTtexturesampler texturesampler, unsigned int texture_array_idx, unsigned int mip_level, RTbuffer  buffer);
  
  /**
  * @brief Gets a buffer object handle from a texture sampler
  * 
  * @ingroup TextureSampler
  * 
  * <B>Description</B>
  * 
  * @ref rtTextureSamplerGetBuffer gets a buffer object from
  * \a texturesampler from the specified MIP level and array slice and
  * stores it in \a *buffer.  \a mip_level and \a texture_array_idx
  * specify the MIP level and array slice, respectively.
  * 
  * @param[in]   texturesampler      The texture sampler object to be queried for the buffer
  * @param[in]   texture_array_idx   The array slice index the buffer will be queried from
  * @param[in]   mip_level           The MIP level the buffer will be queried from
  * @param[out]  buffer              The return handle to the buffer attached to the texture sampler
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtTextureSamplerGetBuffer was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtTextureSamplerSetBuffer
  * 
  */
  RTresult RTAPI rtTextureSamplerGetBuffer(RTtexturesampler texturesampler, unsigned int texture_array_idx, unsigned int mip_level, RTbuffer* buffer);

  /**
  * @brief Returns the texture ID of this texture sampler
  * 
  * @ingroup TextureSampler
  * 
  * <B>Description</B>
  * 
  * @ref rtTextureSamplerGetId returns a handle to the texture sampler
  * \a texturesampler to be used in OptiX programs on the device to
  * reference the associated texture. The returned ID cannot be used on
  * the host side. If \a texture_id is \a NULL, the call will return
  * @ref RT_ERROR_INVALID_VALUE.
  * 
  * @param[in]   texturesampler   The texture sampler object to be queried for its ID
  * @param[out]  texture_id       The returned device-side texture ID of the texture sampler
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtTextureSamplerGetId was introduced in OptiX 3.0.
  * 
  * <B>See also</B>
  * @ref rtTextureSamplerCreate
  * 
  */
  RTresult RTAPI rtTextureSamplerGetId(RTtexturesampler texturesampler, int* texture_id);

/************************************
 **
 **    Buffer object
 **
 ***********************************/
  
  /**
  * @brief Creates a new buffer object
  * 
  * @ingroup Buffer
  * 
  * <B>Description</B>
  * 
  * @ref rtBufferCreate allocates and returns a new handle to a new buffer object in \a *buffer associated
  * with \a context. The backing storage of the buffer is managed by OptiX. A buffer is specified by a bitwise 
  * \a or combination of a \a type and \a flags in \a bufferdesc. The supported types are:
  * 
  * -  @ref RT_BUFFER_INPUT
  * -  @ref RT_BUFFER_OUTPUT
  * -  @ref RT_BUFFER_INPUT_OUTPUT
  * 
  * The type values are used to specify the direction of data flow from the host to the OptiX devices.
  * @ref RT_BUFFER_INPUT specifies that the host may only write to the buffer and the device may only read from the buffer.
  * @ref RT_BUFFER_OUTPUT specifies the opposite, read only access on the host and write only access on the device.
  * Devices and the host may read and write from buffers of type @ref RT_BUFFER_INPUT_OUTPUT.  Reading or writing to
  * a buffer of the incorrect type (e.g., the host writing to a buffer of type @ref RT_BUFFER_OUTPUT) is undefined.
  * 
  * The supported flags are:
  * 
  * -  @ref RT_BUFFER_GPU_LOCAL
  * -  @ref RT_BUFFER_COPY_ON_DIRTY
  * 
  * Flags can be used to optimize data transfers between the host and its devices. The flag @ref RT_BUFFER_GPU_LOCAL can only be 
  * used in combination with @ref RT_BUFFER_INPUT_OUTPUT. @ref RT_BUFFER_INPUT_OUTPUT and @ref RT_BUFFER_GPU_LOCAL used together specify a buffer 
  * that allows the host to \a only write, and the device to read \a and write data. The written data will never be visible 
  * on the host side and will generally not be visible or other devices.
  *
  * If @ref rtBufferSetDevicePointer or @ref rtBufferGetDevicePointer have been called for a single device for a given buffer,
  * the user can change the buffer's content on that device. The new buffer contents must be synchronized to all devices.
  * These synchronization copies occur at every @ref rtContextLaunch "rtContextLaunch", unless the buffer is declared with @ref RT_BUFFER_COPY_ON_DIRTY.
  * In this case, use @ref rtBufferMarkDirty to notify OptiX that the buffer has been dirtied and must be synchronized.
  * 
  * @param[in]   context      The context to create the buffer in
  * @param[in]   bufferdesc   Bitwise \a or combination of the \a type and \a flags of the new buffer
  * @param[out]  buffer       The return handle for the buffer object
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtBufferCreate was introduced in OptiX 1.0.
  * 
  * @ref RT_BUFFER_GPU_LOCAL was introduced in OptiX 2.0.
  * 
  * <B>See also</B>
  * @ref rtBufferCreateFromGLBO,
  * @ref rtBufferDestroy,
  * @ref rtBufferMarkDirty
  * 
  */
  RTresult RTAPI rtBufferCreate(RTcontext context, unsigned int bufferdesc, RTbuffer* buffer);
  
  /**
  * @brief Destroys a buffer object
  * 
  * @ingroup Buffer
  * 
  * <B>Description</B>
  * 
  * @ref rtBufferDestroy removes \a buffer from its context and deletes it.
  * \a buffer should be a value returned by @ref rtBufferCreate.
  * After the call, \a buffer is no longer a valid handle.
  * Any API object that referenced \a buffer will have its reference invalidated.
  * 
  * @param[in]   buffer   Handle of the buffer to destroy
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtBufferDestroy was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtBufferCreate,
  * @ref rtBufferCreateFromGLBO
  * 
  */
  RTresult RTAPI rtBufferDestroy(RTbuffer buffer);
  
  /**
  * @brief Validates the state of a buffer
  * 
  * @ingroup Buffer
  * 
  * <B>Description</B>
  * 
  * @ref rtBufferValidate checks \a buffer for completeness.  If \a buffer has not had its dimensionality, size or format
  * set, this call will return @ref RT_ERROR_INVALID_CONTEXT.
  * 
  * @param[in]   buffer   The buffer to validate
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtBufferValidate was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtBufferCreate,
  * @ref rtBufferCreateFromGLBO
  * @ref rtContextValidate
  * 
  */
  RTresult RTAPI rtBufferValidate(RTbuffer buffer);
  
  /**
  * @brief Returns the context object that created this buffer
  * 
  * @ingroup Buffer
  * 
  * <B>Description</B>
  * 
  * @ref rtBufferGetContext returns a handle to the context that created \a buffer in \a *context.
  * If \a *context is \a NULL, the call will return @ref RT_ERROR_INVALID_VALUE.
  * 
  * @param[in]   buffer    The buffer to be queried for its context
  * @param[out]  context   The return handle for the buffer's context
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtBufferGetContext was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtContextCreate
  * 
  */
  RTresult RTAPI rtBufferGetContext(RTbuffer buffer, RTcontext* context);

  /**
  * @brief Sets the format of this buffer
  * 
  * @ingroup Buffer
  * 
  * <B>Description</B>
  * 
  * @ref rtBufferSetFormat changes the \a format of \a buffer to the specified value.
  * The data elements of the buffer will have the specified type and can either be
  * vector formats, or a user-defined type whose size is specified with
  * @ref rtBufferSetElementSize. Possible values for \a format are:
  * 
  *   - @ref RT_FORMAT_FLOAT
  *   - @ref RT_FORMAT_FLOAT2
  *   - @ref RT_FORMAT_FLOAT3
  *   - @ref RT_FORMAT_FLOAT4
  *   - @ref RT_FORMAT_BYTE
  *   - @ref RT_FORMAT_BYTE2
  *   - @ref RT_FORMAT_BYTE3
  *   - @ref RT_FORMAT_BYTE4
  *   - @ref RT_FORMAT_UNSIGNED_BYTE
  *   - @ref RT_FORMAT_UNSIGNED_BYTE2
  *   - @ref RT_FORMAT_UNSIGNED_BYTE3
  *   - @ref RT_FORMAT_UNSIGNED_BYTE4
  *   - @ref RT_FORMAT_SHORT
  *   - @ref RT_FORMAT_SHORT2
  *   - @ref RT_FORMAT_SHORT3
  *   - @ref RT_FORMAT_SHORT4
  *   - @ref RT_FORMAT_UNSIGNED_SHORT
  *   - @ref RT_FORMAT_UNSIGNED_SHORT2
  *   - @ref RT_FORMAT_UNSIGNED_SHORT3
  *   - @ref RT_FORMAT_UNSIGNED_SHORT4
  *   - @ref RT_FORMAT_INT
  *   - @ref RT_FORMAT_INT2
  *   - @ref RT_FORMAT_INT3
  *   - @ref RT_FORMAT_INT4
  *   - @ref RT_FORMAT_UNSIGNED_INT
  *   - @ref RT_FORMAT_UNSIGNED_INT2
  *   - @ref RT_FORMAT_UNSIGNED_INT3
  *   - @ref RT_FORMAT_UNSIGNED_INT4
  *   - @ref RT_FORMAT_USER
  * 
  * @param[in]   buffer   The buffer to have its format set
  * @param[in]   format   The target format of the buffer
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtBufferSetFormat was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtBufferSetFormat,
  * @ref rtBufferGetFormat,
  * @ref rtBufferGetFormat,
  * @ref rtBufferGetElementSize,
  * @ref rtBufferSetElementSize
  * 
  */
  RTresult RTAPI rtBufferSetFormat(RTbuffer buffer, RTformat  format);
  
  /**
  * @brief Gets the format of this buffer
  * 
  * @ingroup Buffer
  * 
  * <B>Description</B>
  * 
  * @ref rtBufferGetFormat returns, in \a *format, the format of \a buffer.  See @ref rtBufferSetFormat for a listing
  * of @ref RTbuffer values.
  * 
  * @param[in]   buffer   The buffer to be queried for its format
  * @param[out]  format   The return handle for the buffer's format
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtBufferGetFormat was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtBufferSetFormat,
  * @ref rtBufferGetFormat
  * 
  */
  RTresult RTAPI rtBufferGetFormat(RTbuffer buffer, RTformat* format);
  
  /**
  * @brief Modifies the size in bytes of a buffer's individual elements
  * 
  * @ingroup Buffer
  * 
  * <B>Description</B>
  * 
  * @ref rtBufferSetElementSize modifies the size in bytes of a buffer's user-formatted
  * elements. The target buffer is specified by \a buffer, which should be a
  * value returned by @ref rtBufferCreate and should have format @ref RT_FORMAT_USER.
  * The new size of the buffer's individual elements is specified by
  * \a element_size and should be a value not equal to 0. If the buffer has
  * format @ref RT_FORMAT_USER, and \a element_size is not equal to 0, then after
  * the call, the buffer's individual elements shall have size equal to
  * \a element_size and all storage associated with the buffer shall be reset.
  * Otherwise, this call has no effect and returns either @ref RT_ERROR_TYPE_MISMATCH if
  * the buffer does not have format @ref RT_FORMAT_USER or @ref RT_ERROR_INVALID_VALUE if the
  * buffer has format @ref RT_FORMAT_USER but \a element_size is equal to 0.
  * 
  * @param[in]   buffer            Specifies the buffer to be modified
  * @param[in]   size_of_element   Specifies the new size in bytes of the buffer's individual elements
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_TYPE_MISMATCH
  * 
  * <B>History</B>
  * 
  * @ref rtBufferSetElementSize was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtBufferGetElementSize,
  * @ref rtBufferCreate
  * 
  */
  RTresult RTAPI rtBufferSetElementSize(RTbuffer buffer, RTsize  size_of_element);
  
  /**
  * @brief Returns the size of a buffer's individual elements
  * 
  * @ingroup Buffer
  * 
  * <B>Description</B>
  * 
  * @ref rtBufferGetElementSize queries the size of a buffer's elements. The target buffer
  * is specified by \a buffer, which should be a value returned by
  * @ref rtBufferCreate. After the call, the size, in bytes, of the buffer's
  * individual elements shall be returned in \a *element_size_return, if it is not
  * \a NULL. Otherwise, this call has no effect.
  * 
  * @param[in]   buffer                Specifies the buffer to be queried
  * @param[out]  size_of_element       Returns the size of the buffer's individual elements
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_UNKNOWN
  * 
  * <B>History</B>
  * 
  * @ref rtBufferGetElementSize was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtBufferSetElementSize,
  * @ref rtBufferCreate
  * 
  */
  RTresult RTAPI rtBufferGetElementSize(RTbuffer buffer, RTsize* size_of_element);

  /**
  * @brief Sets the width and dimensionality of this buffer
  * 
  * @ingroup Buffer
  * 
  * <B>Description</B>
  * 
  * @ref rtBufferSetSize1D sets the dimensionality of \a buffer to 1 and sets its width to
  * \a width.
  * 
  * @param[in]   buffer   The buffer to be resized
  * @param[in]   width    The width of the resized buffer
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_ALREADY_MAPPED
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtBufferSetSize1D was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtBufferSetSize2D,
  * @ref rtBufferSetSize3D,
  * @ref rtBufferSetSizev,
  * @ref rtBufferGetSize1D,
  * @ref rtBufferGetSize2D,
  * @ref rtBufferGetSize3D,
  * @ref rtBufferGetSizev
  * 
  */
  RTresult RTAPI rtBufferSetSize1D(RTbuffer buffer, RTsize  width);
  
  /**
  * @brief Get the width of this buffer
  * 
  * @ingroup Buffer
  * 
  * <B>Description</B>
  * 
  * @ref rtBufferGetSize1D stores the width of \a buffer in \a *width.
  * 
  * @param[in]   buffer   The buffer to be queried for its dimensions
  * @param[out]  width    The return handle for the buffer's width
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtBufferGetSize1D was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtBufferSetSize1D,
  * @ref rtBufferSetSize2D,
  * @ref rtBufferSetSize3D,
  * @ref rtBufferSetSizev,
  * @ref rtBufferGetSize2D,
  * @ref rtBufferGetSize3D,
  * @ref rtBufferGetSizev
  * 
  */
  RTresult RTAPI rtBufferGetSize1D(RTbuffer buffer, RTsize* width);
  
  /**
  * @brief Sets the width, height and dimensionality of this buffer
  * 
  * @ingroup Buffer
  * 
  * <B>Description</B>
  * 
  * @ref rtBufferSetSize2D sets the dimensionality of \a buffer to 2 and sets its width
  * and height to \a width and \a height, respectively.  If \a width or \a height is
  * zero, they both must be zero.
  * 
  * @param[in]   buffer   The buffer to be resized
  * @param[in]   width    The width of the resized buffer
  * @param[in]   height   The height of the resized buffer
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_ALREADY_MAPPED
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtBufferSetSize2D was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtBufferSetSize1D,
  * @ref rtBufferSetSize3D,
  * @ref rtBufferSetSizev,
  * @ref rtBufferGetSize1D,
  * @ref rtBufferGetSize2D,
  * @ref rtBufferGetSize3D,
  * @ref rtBufferGetSizev
  * 
  */
  RTresult RTAPI rtBufferSetSize2D(RTbuffer buffer, RTsize width, RTsize height);
  
  /**
  * @brief Gets the width and height of this buffer
  * 
  * @ingroup Buffer
  * 
  * <B>Description</B>
  * 
  * @ref rtBufferGetSize2D stores the width and height of \a buffer in \a *width and
  * \a *height, respectively.
  * 
  * @param[in]   buffer   The buffer to be queried for its dimensions
  * @param[out]  width    The return handle for the buffer's width
  * @param[out]  height   The return handle for the buffer's height
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtBufferGetSize2D was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtBufferSetSize1D,
  * @ref rtBufferSetSize2D,
  * @ref rtBufferSetSize3D,
  * @ref rtBufferSetSizev,
  * @ref rtBufferGetSize1D,
  * @ref rtBufferGetSize3D,
  * @ref rtBufferGetSizev
  * 
  */
  RTresult RTAPI rtBufferGetSize2D(RTbuffer buffer, RTsize* width, RTsize* height);
  
  /**
  * @brief Sets the width, height, depth and dimensionality of a buffer
  * 
  * @ingroup Buffer
  * 
  * <B>Description</B>
  * 
  * @ref rtBufferSetSize3D sets the dimensionality of \a buffer to 3 and sets its width,
  * height and depth to \a width, \a height and \a depth, respectively.  If \a width,
  * \a height or \a depth is zero, they all must be zero.
  * 
  * @param[in]   buffer   The buffer to be resized
  * @param[in]   width    The width of the resized buffer
  * @param[in]   height   The height of the resized buffer
  * @param[in]   depth    The depth of the resized buffer
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_ALREADY_MAPPED
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtBufferSetSize3D was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtBufferSetSize2D,
  * @ref rtBufferSetSize3D,
  * @ref rtBufferSetSizev,
  * @ref rtBufferGetSize1D,
  * @ref rtBufferGetSize2D,
  * @ref rtBufferGetSize3D,
  * @ref rtBufferGetSizev
  * 
  */
  RTresult RTAPI rtBufferSetSize3D(RTbuffer buffer, RTsize width, RTsize height, RTsize depth);
  
  /**
  * @brief Gets the width, height and depth of this buffer
  * 
  * @ingroup Buffer
  * 
  * <B>Description</B>
  * 
  * @ref rtBufferGetSize3D stores the width, height and depth of \a buffer in \a *width,
  * \a *height and \a *depth, respectively.
  * 
  * @param[in]   buffer   The buffer to be queried for its dimensions
  * @param[out]  width    The return handle for the buffer's width
  * @param[out]  height   The return handle for the buffer's height
  * @param[out]  depth    The return handle for the buffer's depth
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtBufferGetSize3D was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtBufferSetSize1D,
  * @ref rtBufferSetSize2D,
  * @ref rtBufferSetSize3D,
  * @ref rtBufferSetSizev,
  * @ref rtBufferGetSize1D,
  * @ref rtBufferGetSize2D,
  * @ref rtBufferGetSizev
  * 
  */
  RTresult RTAPI rtBufferGetSize3D(RTbuffer buffer, RTsize* width, RTsize* height, RTsize* depth);
  
  /**
  * @brief Sets the dimensionality and dimensions of a buffer
  * 
  * @ingroup Buffer
  * 
  * <B>Description</B>
  * 
  * @ref rtBufferSetSizev sets the dimensionality of \a buffer to \a dimensionality and
  * sets the dimensions of the buffer to the values stored at *\a dims, which must contain
  * a number of values equal to \a dimensionality.  If any of values of \a dims is zero
  * they must all be zero.
  * 
  * @param[in]   buffer           The buffer to be resized
  * @param[in]   dimensionality   The dimensionality the buffer will be resized to
  * @param[in]   dims             The array of sizes for the dimension of the resize
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_ALREADY_MAPPED
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtBufferSetSizev was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtBufferSetSize1D,
  * @ref rtBufferSetSize2D,
  * @ref rtBufferSetSize3D,
  * @ref rtBufferGetSize1D,
  * @ref rtBufferGetSize2D,
  * @ref rtBufferGetSize3D,
  * @ref rtBufferGetSizev
  * 
  */
  RTresult RTAPI rtBufferSetSizev(RTbuffer buffer, unsigned int dimensionality, const RTsize* dims);
  
  /**
  * @brief Gets the dimensions of this buffer
  * 
  * @ingroup Buffer
  * 
  * <B>Description</B>
  * 
  * @ref rtBufferGetSizev stores the dimensions of \a buffer in \a *dims.  The number of
  * dimensions returned is specified by \a dimensionality.  The storage at \a dims must be
  * large enough to hold the number of requested buffer dimensions.
  * 
  * @param[in]   buffer           The buffer to be queried for its dimensions
  * @param[in]   dimensionality   The number of requested dimensions
  * @param[out]  dims             The array of dimensions the call will store to
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtBufferGetSizev was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtBufferGetDimensionality
  * 
  */
  RTresult RTAPI rtBufferGetSizev(RTbuffer buffer, unsigned int dimensionality, RTsize* dims);

  /**
  * @brief Gets the dimensionality of this buffer object
  * 
  * @ingroup Buffer
  * 
  * <B>Description</B>
  * 
  * @ref rtBufferGetDimensionality returns the dimensionality of \a buffer in \a
  * *dimensionality.  The value returned will be one of 1, 2 or 3, corresponding to 1D, 2D
  * and 3D buffers, respectively.
  * 
  * @param[in]   buffer           The buffer to be queried for its dimensionality
  * @param[out]  dimensionality   The return handle for the buffer's dimensionality
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtBufferGetDimensionality was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * \a rtBufferSetSize{1-2-3}D
  * 
  */
  RTresult RTAPI rtBufferGetDimensionality(RTbuffer buffer, unsigned int* dimensionality);

  /**
  * @brief Maps a buffer object to the host
  * 
  * @ingroup Buffer
  * 
  * <B>Description</B>
  * 
  * @ref rtBufferMap returns a pointer, accessible by the host, in \a *user_pointer that
  * contains a mapped copy of the contents of \a buffer.  The memory pointed to by \a
  * *user_pointer can be written to or read from, depending on the type of \a buffer.  For
  * example, this code snippet demonstrates creating and filling an input buffer with
  * floats.
  * 
  *@code
  *  RTbuffer buffer;
  *  float* data;
  *  rtBufferCreate(context, RT_BUFFER_INPUT, &buffer);
  *  rtBufferSetFormat(buffer, RT_FORMAT_FLOAT);
  *  rtBufferSetSize1D(buffer, 10);
  *  rtBufferMap(buffer, (void*)&data);
  *  for(int i = 0; i < 10; ++i)
  *    data[i] = 4.f * i;
  *  rtBufferUnmap(buffer);
  *@endcode
  * If \a buffer has already been mapped, the call will return @ref RT_ERROR_ALREADY_MAPPED.
  * 
  * @param[in]   buffer         The buffer to be mapped
  * @param[out]  user_pointer   Return handle to a user pointer where the buffer will be mapped to
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_ALREADY_MAPPED
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtBufferMap was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtBufferUnmap
  * 
  */
  RTresult RTAPI rtBufferMap(RTbuffer buffer, void** user_pointer);
  
  /**
  * @brief Unmaps a buffer's storage from the host
  * 
  * @ingroup Buffer
  * 
  * <B>Description</B>
  * 
  * @ref rtBufferUnmap unmaps a buffer from the host after a call to @ref rtBufferMap.  @ref rtContextLaunch "rtContextLaunch" cannot be called
  * while buffers are still mapped to the host.  A call to @ref rtBufferUnmap that does not follow a matching @ref rtBufferMap
  * call will return @ref RT_ERROR_INVALID_VALUE.
  * 
  * @param[in]   buffer   The buffer to unmap
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_CONTEXT
  * - @ref RT_ERROR_INVALID_VALUE
  * - @ref RT_ERROR_MEMORY_ALLOCATION_FAILED
  * 
  * <B>History</B>
  * 
  * @ref rtBufferUnmap was introduced in OptiX 1.0.
  * 
  * <B>See also</B>
  * @ref rtBufferMap
  * 
  */
  RTresult RTAPI rtBufferUnmap(RTbuffer buffer);

  /**
  * @brief Gets an id suitable for use with buffers of buffers
  * 
  * @ingroup Buffer
  * 
  * <B>Description</B>
  * 
  * @ref rtBufferGetId returns an ID for the provided buffer.  The returned ID is used on
  * the device to reference the buffer.  It needs to be copied into a buffer of type @ref
  * RT_FORMAT_BUFFER_ID or used in a @ref rtBufferId object.. If \a *buffer_id is \a NULL
  * or the \a buffer is not a valid RTbuffer, the call will return @ref
  * RT_ERROR_INVALID_VALUE.  @ref RT_BUFFER_ID_NULL can be used as a sentinal for a
  * non-existent buffer, since this value will never be returned as a valid buffer id.
  * 
  * @param[in]   buffer      The buffer to be queried for its id
  * @param[out]  buffer_id   The returned ID of the buffer
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtBufferGetId was introduced in OptiX 3.5.
  * 
  * <B>See also</B>
  * @ref rtContextGetBufferFromId
  * 
  */
  RTresult RTAPI rtBufferGetId(RTbuffer buffer, int* buffer_id);
  
  /**
  * @brief Gets an RTbuffer corresponding to the buffer id
  * 
  * @ingroup Buffer
  * 
  * <B>Description</B>
  * 
  * @ref rtContextGetBufferFromId returns a handle to the buffer in \a *buffer corresponding to
  * the \a buffer_id supplied.  If \a buffer_id does not map to a valid buffer handle,
  * \a *buffer is \a NULL or if \a context is invalid, the call will return
  * @ref RT_ERROR_INVALID_VALUE.
  * 
  * @param[in]   context     The context the buffer should be originated from
  * @param[in]   buffer_id   The ID of the buffer to query
  * @param[out]  buffer      The return handle for the buffer object corresponding to the buffer_id
  * 
  * <B>Return values</B>
  *
  * Relevant return values:
  * - @ref RT_SUCCESS
  * - @ref RT_ERROR_INVALID_VALUE
  * 
  * <B>History</B>
  * 
  * @ref rtContextGetBufferFromId was introduced in OptiX 3.5.
  * 
  * <B>See also</B>
  * @ref rtBufferGetId
  * 
  */
  RTresult RTAPI rtContextGetBufferFromId(RTcontext context, int buffer_id, RTbuffer* buffer);

#ifdef __cplusplus
}
#endif

#endif /* __optix_optix_host_h__ */
