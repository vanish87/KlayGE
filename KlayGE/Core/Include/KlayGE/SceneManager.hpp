// SceneManager.hpp
// KlayGE ������������ ͷ�ļ�
// Ver 3.12.0
// ��Ȩ����(C) ������, 2003-2011
// Homepage: http://www.klayge.org
//
// 3.11.0
// ��DoAddSceneObject/DoDelSceneObject��ΪOnAddSceneObject/OnDelSceneObject (2010.11.16)
//
// 3.9.0
// ������SceneObjects (2009.7.30)
//
// 2.4.0
// ������NumObjectsRendered��NumPrimitivesRendered��NumVerticesRendered (2005.3.20)
//
// �޸ļ�¼
//////////////////////////////////////////////////////////////////////////////////

#ifndef _SCENEMANAGER_HPP
#define _SCENEMANAGER_HPP

#pragma once

#include <KlayGE/PreDeclare.hpp>

#include <KlayGE/Renderable.hpp>
#include <KFL/Frustum.hpp>
#include <KFL/Thread.hpp>

#include <vector>
#include <unordered_map>

#include <boost/noncopyable.hpp>

namespace KlayGE
{
	class KLAYGE_CORE_API SceneManager : boost::noncopyable
	{
	public:
		SceneManager();
		virtual ~SceneManager();

		void Suspend();
		void Resume();

		void SmallObjectThreshold(float area);
		void SceneUpdateElapse(float elapse);
		virtual void ClipScene();

		void AddCamera(CameraPtr const & camera);
		void DelCamera(CameraPtr const & camera);

		uint32_t NumCameras() const;
		CameraPtr& GetCamera(uint32_t index);
		CameraPtr const & GetCamera(uint32_t index) const;

		void AddLight(LightSourcePtr const & light);
		void DelLight(LightSourcePtr const & light);

		uint32_t NumLights() const;
		LightSourcePtr& GetLight(uint32_t index);
		LightSourcePtr const & GetLight(uint32_t index) const;

		void AddSceneObject(SceneObjectPtr const & obj);
		void AddSceneObjectLocked(SceneObjectPtr const & obj);
		void DelSceneObject(SceneObjectPtr const & obj);
		void DelSceneObjectLocked(SceneObjectPtr const & obj);
		void AddRenderable(Renderable* obj);

		uint32_t NumSceneObjects() const;
		SceneObjectPtr& GetSceneObject(uint32_t index);
		SceneObjectPtr const & GetSceneObject(uint32_t index) const;

		virtual BoundOverlap AABBVisible(AABBox const & aabb) const;
		virtual BoundOverlap OBBVisible(OBBox const & obb) const;
		virtual BoundOverlap SphereVisible(Sphere const & sphere) const;
		virtual BoundOverlap FrustumVisible(Frustum const & frustum) const;

		virtual void ClearCamera();
		virtual void ClearLight();
		virtual void ClearObject();

		void Update();

		uint32_t NumObjectsRendered() const;
		uint32_t NumRenderablesRendered() const;
		uint32_t NumPrimitivesRendered() const;
		uint32_t NumVerticesRendered() const;
		uint32_t NumDrawCalls() const;
		uint32_t NumDispatchCalls() const;

	protected:
		void Flush(uint32_t urt);

		std::vector<CameraPtr>::iterator DelCamera(std::vector<CameraPtr>::iterator iter);
		std::vector<LightSourcePtr>::iterator DelLight(std::vector<LightSourcePtr>::iterator iter);
		std::vector<SceneObjectPtr>::iterator DelSceneObject(std::vector<SceneObjectPtr>::iterator iter);
		std::vector<SceneObjectPtr>::iterator DelSceneObjectLocked(std::vector<SceneObjectPtr>::iterator iter);
		virtual void OnAddSceneObject(SceneObjectPtr const & obj) = 0;
		virtual void OnDelSceneObject(std::vector<SceneObjectPtr>::iterator iter) = 0;
		virtual void DoSuspend() = 0;
		virtual void DoResume() = 0;

		void UpdateThreadFunc();

		BoundOverlap VisibleTestFromParent(SceneObject* obj, float3 const & eye_pos, float4x4 const & view_proj);

	protected:
		std::vector<CameraPtr> cameras_;
		Frustum const * frustum_;
		std::vector<LightSourcePtr> lights_;
		std::vector<SceneObjectPtr> scene_objs_;
		std::vector<SceneObjectPtr> overlay_scene_objs_;

		std::unordered_map<size_t, std::shared_ptr<std::vector<BoundOverlap>>> visible_marks_map_;

		float small_obj_threshold_;
		float update_elapse_;

	private:
		void FlushScene();

	private:
		uint32_t urt_;

		std::vector<std::pair<RenderTechnique const *, std::vector<Renderable*>>> render_queue_;

		uint32_t num_objects_rendered_;
		uint32_t num_renderables_rendered_;
		uint32_t num_primitives_rendered_;
		uint32_t num_vertices_rendered_;
		uint32_t num_draw_calls_;
		uint32_t num_dispatch_calls_;

		std::mutex update_mutex_;
		std::unique_ptr<joiner<void>> update_thread_;
		volatile bool quit_;

		bool deferred_mode_;
	};
}

#endif			// _SCENEMANAGER_HPP
