/****************************************************************************************

Copyright (C) 2013 Autodesk, Inc.
All rights reserved.

Use of this software is subject to the terms of the Autodesk license agreement
provided at the time of installation or download, or which otherwise accompanies
this software in either electronic or hard copy form.

****************************************************************************************/

#ifndef _SCENE_CACHE_H
#define _SCENE_CACHE_H

#include <OpenGL.hh>
#include <fbxsdk.h>

#include <stdint.h>

#include <tinythread.h>

// Save mesh vertices, normals, UVs and indices in GPU with OpenGL Vertex Buffer Objects
class VBOMesh
{
public:
	VBOMesh();
	VBOMesh(const VBOMesh &oth);
	~VBOMesh();

    // Save up data into GPU buffers.
	bool Initialize(const FbxMesh * pMesh);

    // Update vertex positions for deformed meshes.
    void UpdateVertexPosition(const FbxMesh * pMesh, const FbxVector4 * pVertices);

	void UploadNextFrame();

    // Bind buffers, set vertex arrays, turn on lighting and texture.
    void BeginDraw() const;
    // Draw all the faces with specific material with given shading mode.
    void Draw(int pMaterialIndex) const;
    // Unbind buffers, reset vertex arrays, turn off lighting and texture.
    void EndDraw() const;

    // Get the count of material groups
    int GetSubMeshCount() const { return mSubMeshes.GetCount(); }

private:
    enum
    {
        VERTEX_VBO,
        NORMAL_VBO,
        UV_VBO,
        INDEX_VBO,
        VBO_COUNT,
    };

    // For every material, record the offsets in every VBO and triangle counts
    struct SubMesh
    {
        SubMesh() : IndexOffset(0), TriangleCount(0) {}

        int IndexOffset;
        int TriangleCount;
    };

	void			*mNextFrameTransform;
	uint32_t		mNextFrameVertexCount;

	uint32_t		mVBOPolyCount;
	uint32_t		mVBOPolyVertexCount;

	GLuint mVBONames[VBO_COUNT];
    FbxArray<SubMesh*> mSubMeshes;
    bool mHasNormal;
    bool mHasUV;
    bool mAllByControlPoint; // Save data in VBO by control point or by polygon vertex.
};

// Cache for FBX material
class MaterialCache
{
public:
    MaterialCache();
    ~MaterialCache();

    bool Initialize(const FbxSurfaceMaterial * pMaterial);
    
    // Set material colors and binding diffuse texture if exists.
    void SetCurrentMaterial() const;

    bool HasTexture() const { return mDiffuse.mTextureName != 0; }

    // Set default green color.
    static void SetDefaultMaterial();

private:
    struct ColorChannel
    {
        ColorChannel() : mTextureName(0)
        {
            mColor[0] = 0.0f;
            mColor[1] = 0.0f;
            mColor[2] = 0.0f;
            mColor[3] = 1.0f;
        }

        GLuint mTextureName;
        GLfloat mColor[4];
    };
    ColorChannel mEmissive;
    ColorChannel mAmbient;
    ColorChannel mDiffuse;
    ColorChannel mSpecular;
    GLfloat mShinness;
};

// Property cache, value and animation curve.
struct PropertyChannel
{
    PropertyChannel() : mAnimCurve(NULL), mValue(0.0f) {}
    // Query the channel value at specific time.
    GLfloat Get(const FbxTime & pTime) const
    {
        if (mAnimCurve)
        {
            return mAnimCurve->Evaluate(pTime);
        }
        else
        {
            return mValue;
        }
    }

    FbxAnimCurve * mAnimCurve;
    GLfloat mValue;
};

#endif // _SCENE_CACHE_H
