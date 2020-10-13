
#include "SkeletalMeshComponent.h"
#include "Serialization/Serializer.h"
#include "RunTime/SkeletalMesh/SkeletalMeshInstance.h"
#include "RunTime/Resource/ResourceManager.h"

namespace inceptionengine
{

	SkeletalMeshComponent::SkeletalMeshComponent(SkeletalMeshRenderSystem& system)
		:mSystem(system)
	{
		mSkeletalMeshInstance = std::make_unique<SkeletalMeshInstance>();
	}

	SkeletalMeshComponent::~SkeletalMeshComponent() = default;

	SkeletalMeshComponent::SkeletalMeshComponent(SkeletalMeshComponent&&) noexcept = default;


	void SkeletalMeshComponent::SetTriangle()
	{
		Vertex v1 = {};
		v1.position = glm::vec4(85.9174652f, -33.0414543f, -0.677608311f, 1.0f);
		v1.texCoord = glm::vec3(RandFloat(0.0f,1.0f), RandFloat(0.0f, 1.0f), 0.0f);
		Vertex v2 = {};
		v2.position = glm::vec4(85.3564911f, -33.2652740f, -0.67933947f, 1.0f);
		v2.texCoord = glm::vec3(RandFloat(0.0f, 1.0f), RandFloat(0.0f, 1.0f), 0.0f);
		Vertex v3 = {};
		v3.position = glm::vec4(85.2866364f, -32.6977081f, -0.674987137f, 1.0f);
		v3.texCoord = glm::vec3(RandFloat(0.0f, 1.0f), RandFloat(0.0f, 1.0f), 0.0f);

		std::vector<Vertex> triangleVertices = { v1, v2, v3 };
		std::vector<uint32_t> triangleIndices = { 0,1,2 };

		auto triangle = std::make_shared<SkeletalMesh>();
		triangle->mSubMeshes.resize(1);
		triangle->mSubMeshes[0].vertices = triangleVertices;
		triangle->mSubMeshes[0].indices = triangleIndices;
		triangle->mSubMeshes[0].texturePath = "StandAloneResource\\T_Grass.BMP";
		triangle->mSubMeshes[0].shaderPath =
		{
			"EngineResource\\shader\\spv\\vertex.spv",
			"EngineResource\\shader\\spv\\fragment.spv"
		};

		mSkeletalMeshInstance->mSkeletalMesh = triangle;

		mSkeletalMeshInstance->InitializeRenderObjects();
	}

	void SkeletalMeshComponent::ImportMesh(std::string const& fbxFilePath)
	{
		//fbximport::ImportScene importScene;
		//fbximport::Import(fbxFilePath, importScene);

		mSkeletalMeshInstance->mSkeletalMesh = gResourceMgr.GetResource<SkeletalMesh>(fbxFilePath);


		mSkeletalMeshInstance->InitializeRenderObjects();

		//mSkeletalMeshInstance->mCurrentPose = importScene.pose;
	}

	void SkeletalMeshComponent::SetMesh(std::string const& meshFilePath)
	{
		assert(false && "this function is not ready to use yet");
		
		/*
		mSkeletalMeshInstance.mSkeletalMesh = Serializer::Deserailize<SkeletalMesh>(meshFilePath);

		size_t numSubMeshes = mSkeletalMeshInstance.mSkeletalMesh->mSubMeshes.size();
		InitializeRendererObjects(numSubMeshes);
		*/
	}

	void SkeletalMeshComponent::SetPlane()
	{
		Vertex v1 = {};
		v1.position = glm::vec4(500.0f, 0.0f, 500.0f, 1.0f);
		v1.texCoord = glm::vec3(0.0f, 0.0f, 0.0f);
		v1.normal = glm::vec3(0.0f, 1.0f, 0.0f);
		Vertex v2 = {};
		v2.position = glm::vec4(-500.0f, 0.0f, 500.0f, 1.0f);
		v2.texCoord = glm::vec3(0.0f, 1.0f, 0.0f);
		v2.normal = glm::vec3(0.0f, 1.0f, 0.0f);
		Vertex v3 = {};
		v3.position = glm::vec4(-500.0f, 0.0f, -500.0f, 1.0f);
		v3.texCoord = glm::vec3(1.0f, 1.0f, 0.0f);
		v3.normal = glm::vec3(0.0f, 1.0f, 0.0f);
		Vertex v4 = {};
		v4.position = glm::vec4(500.0f, 0.0f, -500.0f, 1.0f);
		v4.texCoord = glm::vec3(1.0f, 0.0f, 0.0f);
		v4.normal = glm::vec3(0.0f, 1.0f, 0.0f);


		std::vector<Vertex> planeVertices = { v1, v2, v3, v4 };
		std::vector<uint32_t> planeIndices = { 0,1,2,2,3,0 };

		auto plane = std::make_shared<SkeletalMesh>();
		plane->mSubMeshes.resize(1);
		plane->mSubMeshes[0].vertices = planeVertices;
		plane->mSubMeshes[0].indices = planeIndices;
		plane->mSubMeshes[0].texturePath = "StandAloneResource\\T_Grass.BMP";
		plane->mSubMeshes[0].shaderPath = 
		{ 
			"EngineResource\\shader\\spv\\vertex.spv",
			"EngineResource\\shader\\spv\\fragment.spv" 
		};

		mSkeletalMeshInstance->mSkeletalMesh = plane;

		mSkeletalMeshInstance->InitializeRenderObjects();
	}


	void SkeletalMeshComponent::SetMeshPose(AnimPose const& pose)
	{
	}
}

