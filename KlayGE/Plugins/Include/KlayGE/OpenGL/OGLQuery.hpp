// OGLQuery.hpp
// KlayGE OpenGL�ڵ������ ʵ���ļ�
// Ver 3.0.0
// ��Ȩ����(C) ������, 2005
// Homepage: http://www.klayge.org
//
// 3.0.0
// ���ν��� (2005.9.27)
//
// �޸ļ�¼
//////////////////////////////////////////////////////////////////////////////////

#ifndef _OGLQUERY_HPP
#define _OGLQUERY_HPP

#pragma once

#include <KlayGE/Query.hpp>

namespace KlayGE
{
	class OGLOcclusionQuery : public OcclusionQuery
	{
	public:
		OGLOcclusionQuery();
		~OGLOcclusionQuery();

		void Begin();
		void End();

		uint64_t SamplesPassed();

	private:
		GLuint query_;
	};

	class OGLConditionalRender : public ConditionalRender
	{
	public:
		OGLConditionalRender();
		~OGLConditionalRender();

		void Begin();
		void End();

		void BeginConditionalRender();
		void EndConditionalRender();

		bool AnySamplesPassed();

	private:
		GLuint query_;
	};

	class OGLTimerQuery : public TimerQuery
	{
	public:
		OGLTimerQuery();
		~OGLTimerQuery();

		void Begin();
		void End();

		double TimeElapsed();

	private:
		GLuint query_;
	};

	class OGLSOStatisticsQuery : public SOStatisticsQuery
	{
	public:
		OGLSOStatisticsQuery();
		~OGLSOStatisticsQuery();

		void Begin();
		void End();

		uint64_t NumPrimitivesWritten() override;
		uint64_t PrimitivesGenerated() override;

	private:
		GLuint primitive_written_query_;
		GLuint primitive_generated_query_;
	};
}

#endif		// _OGLQUERY_HPP
