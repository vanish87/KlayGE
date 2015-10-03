/**
 * @file D3D11Fence.hpp
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

#ifndef _D3D11FENCE_HPP
#define _D3D11FENCE_HPP

#pragma once

#include <map>

#include <KlayGE/Fence.hpp>

namespace KlayGE
{
	class D3D11Fence : public Fence
	{
	public:
		D3D11Fence();

		virtual void Signal(uint64_t id, FenceType ft) KLAYGE_OVERRIDE;
		virtual void Wait(uint64_t id) KLAYGE_OVERRIDE;
		virtual bool Completed(uint64_t id) KLAYGE_OVERRIDE;

	private:
		std::map<uint64_t, ID3D11QueryPtr> fences_;
	};
}

#endif		// _D3D11FENCE_HPP
