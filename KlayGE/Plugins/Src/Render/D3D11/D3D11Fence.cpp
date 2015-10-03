/**
 * @file D3D11Fence.cpp
 * @author Minmin Gong
 *
 * @section DESCRIPTION
 *
 * This source file is part of KlayGE
 * For the latest info, see http://www.klayge.org
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * You may alternatively use this source under the terms of
 * the KlayGE Proprietary License (KPL). You can obtained such a license
 * from http://www.klayge.org/licensing/.
 */

#include <KlayGE/KlayGE.hpp>
#include <KFL/ThrowErr.hpp>
#include <KFL/Util.hpp>
#include <KFL/COMPtr.hpp>
#include <KlayGE/Context.hpp>
#include <KlayGE/RenderFactory.hpp>

#include <KlayGE/D3D11/D3D11RenderEngine.hpp>
#include <KlayGE/D3D11/D3D11Fence.hpp>

namespace KlayGE
{
	D3D11Fence::D3D11Fence()
	{
	}

	void D3D11Fence::Signal(uint64_t id, FenceType ft)
	{
		UNREF_PARAM(ft);

		BOOST_ASSERT(fences_.find(id) == fences_.end());

		D3D11RenderEngine const & re = *checked_cast<D3D11RenderEngine const *>(&Context::Instance().RenderFactoryInstance().RenderEngineInstance());
		ID3D11DevicePtr const & d3d_device = re.D3DDevice();
		ID3D11DeviceContextPtr const & d3d_imm_ctx = re.D3DDeviceImmContext();

		D3D11_QUERY_DESC desc;
		desc.Query = D3D11_QUERY_EVENT;
		desc.MiscFlags = 0;

		ID3D11Query* query;
		d3d_device->CreateQuery(&desc, &query);
		auto fence = MakeCOMPtr(query);
		fences_[id] = fence;

		d3d_imm_ctx->End(fence.get());
	}

	void D3D11Fence::Wait(uint64_t id)
	{
		D3D11RenderEngine const & re = *checked_cast<D3D11RenderEngine const *>(&Context::Instance().RenderFactoryInstance().RenderEngineInstance());
		ID3D11DeviceContextPtr const & d3d_imm_ctx = re.D3DDeviceImmContext();

		auto iter = fences_.find(id);
		BOOST_ASSERT(iter != fences_.end());

		uint64_t ret;
		while (S_OK != d3d_imm_ctx->GetData(iter->second.get(), &ret, sizeof(ret), 0));
		fences_.erase(iter);
	}

	bool D3D11Fence::Completed(uint64_t id)
	{
		auto iter = fences_.find(id);
		if (iter == fences_.end())
		{
			return true;
		}
		else
		{
			D3D11RenderEngine const & re = *checked_cast<D3D11RenderEngine const *>(&Context::Instance().RenderFactoryInstance().RenderEngineInstance());
			ID3D11DeviceContextPtr const & d3d_imm_ctx = re.D3DDeviceImmContext();

			uint64_t ret;
			HRESULT hr = d3d_imm_ctx->GetData(iter->second.get(), &ret, sizeof(ret), 0);
			return (S_OK == hr);
		}
	}
}
