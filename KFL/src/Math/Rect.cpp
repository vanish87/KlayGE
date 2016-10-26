/**
 * @file Rect.cpp
 * @author Minmin Gong
 *
 * @section DESCRIPTION
 *
 * This source file is part of KFL, a subproject of KlayGE
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

#include <KFL/KFL.hpp>

#include <KFL/Rect.hpp>

namespace KlayGE
{
	template Rect_T<float>::Rect_T(float const * rhs) KLAYGE_NOEXCEPT;
	template Rect_T<float>::Rect_T(Rect&& rhs) KLAYGE_NOEXCEPT;
	template Rect_T<float>::Rect_T(float left, float top, float right, float bottom) KLAYGE_NOEXCEPT;
	template Rect const & Rect_T<float>::operator+=(float2 const & rhs) KLAYGE_NOEXCEPT;
	template Rect const & Rect_T<float>::operator+=(int2 const & rhs) KLAYGE_NOEXCEPT;
	template Rect const & Rect_T<float>::operator+=(uint2 const & rhs) KLAYGE_NOEXCEPT;
	template Rect const & Rect_T<float>::operator-=(float2 const & rhs) KLAYGE_NOEXCEPT;
	template Rect const & Rect_T<float>::operator-=(int2 const & rhs) KLAYGE_NOEXCEPT;
	template Rect const & Rect_T<float>::operator-=(uint2 const & rhs) KLAYGE_NOEXCEPT;
	template Rect const & Rect_T<float>::operator+=(Rect const & rhs) KLAYGE_NOEXCEPT;
	template Rect const & Rect_T<float>::operator+=(IRect const & rhs) KLAYGE_NOEXCEPT;
	template Rect const & Rect_T<float>::operator+=(UIRect const & rhs) KLAYGE_NOEXCEPT;
	template Rect const & Rect_T<float>::operator-=(Rect const & rhs) KLAYGE_NOEXCEPT;
	template Rect const & Rect_T<float>::operator-=(IRect const & rhs) KLAYGE_NOEXCEPT;
	template Rect const & Rect_T<float>::operator-=(UIRect const & rhs) KLAYGE_NOEXCEPT;
	template Rect const & Rect_T<float>::operator&=(Rect const & rhs) KLAYGE_NOEXCEPT;
	template Rect const & Rect_T<float>::operator&=(IRect const & rhs) KLAYGE_NOEXCEPT;
	template Rect const & Rect_T<float>::operator&=(UIRect const & rhs) KLAYGE_NOEXCEPT;
	template Rect const & Rect_T<float>::operator|=(Rect const & rhs) KLAYGE_NOEXCEPT;
	template Rect const & Rect_T<float>::operator|=(IRect const & rhs) KLAYGE_NOEXCEPT;
	template Rect const & Rect_T<float>::operator|=(UIRect const & rhs) KLAYGE_NOEXCEPT;
	template Rect& Rect_T<float>::operator=(Rect&& rhs) KLAYGE_NOEXCEPT;
	template Rect const Rect_T<float>::operator+() const KLAYGE_NOEXCEPT;
	template Rect const Rect_T<float>::operator-() const KLAYGE_NOEXCEPT;
	template float Rect_T<float>::Width() const KLAYGE_NOEXCEPT;
	template float Rect_T<float>::Height() const KLAYGE_NOEXCEPT;
	template Size const Rect_T<float>::Size() const KLAYGE_NOEXCEPT;
	template bool Rect_T<float>::IsEmpty() const KLAYGE_NOEXCEPT;
	template bool Rect_T<float>::operator==(Rect const & rhs) const KLAYGE_NOEXCEPT;
	template bool Rect_T<float>::PtInRect(float2 const & pt) const KLAYGE_NOEXCEPT;

	template Rect_T<int32_t>::Rect_T(int32_t const * rhs) KLAYGE_NOEXCEPT;
	template Rect_T<int32_t>::Rect_T(IRect&& rhs) KLAYGE_NOEXCEPT;
	template Rect_T<int32_t>::Rect_T(int32_t left, int32_t top, int32_t right, int32_t bottom) KLAYGE_NOEXCEPT;
	template IRect const & Rect_T<int32_t>::operator+=(float2 const & rhs) KLAYGE_NOEXCEPT;
	template IRect const & Rect_T<int32_t>::operator+=(int2 const & rhs) KLAYGE_NOEXCEPT;
	template IRect const & Rect_T<int32_t>::operator+=(uint2 const & rhs) KLAYGE_NOEXCEPT;
	template IRect const & Rect_T<int32_t>::operator-=(float2 const & rhs) KLAYGE_NOEXCEPT;
	template IRect const & Rect_T<int32_t>::operator-=(int2 const & rhs) KLAYGE_NOEXCEPT;
	template IRect const & Rect_T<int32_t>::operator-=(uint2 const & rhs) KLAYGE_NOEXCEPT;
	template IRect const & Rect_T<int32_t>::operator+=(Rect const & rhs) KLAYGE_NOEXCEPT;
	template IRect const & Rect_T<int32_t>::operator+=(IRect const & rhs) KLAYGE_NOEXCEPT;
	template IRect const & Rect_T<int32_t>::operator+=(UIRect const & rhs) KLAYGE_NOEXCEPT;
	template IRect const & Rect_T<int32_t>::operator-=(Rect const & rhs) KLAYGE_NOEXCEPT;
	template IRect const & Rect_T<int32_t>::operator-=(IRect const & rhs) KLAYGE_NOEXCEPT;
	template IRect const & Rect_T<int32_t>::operator-=(UIRect const & rhs) KLAYGE_NOEXCEPT;
	template IRect const & Rect_T<int32_t>::operator&=(Rect const & rhs) KLAYGE_NOEXCEPT;
	template IRect const & Rect_T<int32_t>::operator&=(IRect const & rhs) KLAYGE_NOEXCEPT;
	template IRect const & Rect_T<int32_t>::operator&=(UIRect const & rhs) KLAYGE_NOEXCEPT;
	template IRect const & Rect_T<int32_t>::operator|=(Rect const & rhs) KLAYGE_NOEXCEPT;
	template IRect const & Rect_T<int32_t>::operator|=(IRect const & rhs) KLAYGE_NOEXCEPT;
	template IRect const & Rect_T<int32_t>::operator|=(UIRect const & rhs) KLAYGE_NOEXCEPT;
	template IRect& Rect_T<int32_t>::operator=(IRect&& rhs) KLAYGE_NOEXCEPT;
	template IRect const Rect_T<int32_t>::operator+() const KLAYGE_NOEXCEPT;
	template IRect const Rect_T<int32_t>::operator-() const KLAYGE_NOEXCEPT;
	template int32_t Rect_T<int32_t>::Width() const KLAYGE_NOEXCEPT;
	template int32_t Rect_T<int32_t>::Height() const KLAYGE_NOEXCEPT;
	template ISize const Rect_T<int32_t>::Size() const KLAYGE_NOEXCEPT;
	template bool Rect_T<int32_t>::IsEmpty() const KLAYGE_NOEXCEPT;
	template bool Rect_T<int32_t>::operator==(IRect const & rhs) const KLAYGE_NOEXCEPT;
	template bool Rect_T<int32_t>::PtInRect(int2 const & pt) const KLAYGE_NOEXCEPT;

	template Rect_T<uint32_t>::Rect_T(uint32_t const * rhs) KLAYGE_NOEXCEPT;
	template Rect_T<uint32_t>::Rect_T(UIRect&& rhs) KLAYGE_NOEXCEPT;
	template Rect_T<uint32_t>::Rect_T(uint32_t left, uint32_t top, uint32_t right, uint32_t bottom) KLAYGE_NOEXCEPT;
	template UIRect const & Rect_T<uint32_t>::operator+=(float2 const & rhs) KLAYGE_NOEXCEPT;
	template UIRect const & Rect_T<uint32_t>::operator+=(int2 const & rhs) KLAYGE_NOEXCEPT;
	template UIRect const & Rect_T<uint32_t>::operator+=(uint2 const & rhs) KLAYGE_NOEXCEPT;
	template UIRect const & Rect_T<uint32_t>::operator-=(float2 const & rhs) KLAYGE_NOEXCEPT;
	template UIRect const & Rect_T<uint32_t>::operator-=(int2 const & rhs) KLAYGE_NOEXCEPT;
	template UIRect const & Rect_T<uint32_t>::operator-=(uint2 const & rhs) KLAYGE_NOEXCEPT;
	template UIRect const & Rect_T<uint32_t>::operator+=(Rect const & rhs) KLAYGE_NOEXCEPT;
	template UIRect const & Rect_T<uint32_t>::operator+=(IRect const & rhs) KLAYGE_NOEXCEPT;
	template UIRect const & Rect_T<uint32_t>::operator+=(UIRect const & rhs) KLAYGE_NOEXCEPT;
	template UIRect const & Rect_T<uint32_t>::operator-=(Rect const & rhs) KLAYGE_NOEXCEPT;
	template UIRect const & Rect_T<uint32_t>::operator-=(IRect const & rhs) KLAYGE_NOEXCEPT;
	template UIRect const & Rect_T<uint32_t>::operator-=(UIRect const & rhs) KLAYGE_NOEXCEPT;
	template UIRect const & Rect_T<uint32_t>::operator&=(Rect const & rhs) KLAYGE_NOEXCEPT;
	template UIRect const & Rect_T<uint32_t>::operator&=(IRect const & rhs) KLAYGE_NOEXCEPT;
	template UIRect const & Rect_T<uint32_t>::operator&=(UIRect const & rhs) KLAYGE_NOEXCEPT;
	template UIRect const & Rect_T<uint32_t>::operator|=(Rect const & rhs) KLAYGE_NOEXCEPT;
	template UIRect const & Rect_T<uint32_t>::operator|=(IRect const & rhs) KLAYGE_NOEXCEPT;
	template UIRect const & Rect_T<uint32_t>::operator|=(UIRect const & rhs) KLAYGE_NOEXCEPT;
	template UIRect& Rect_T<uint32_t>::operator=(UIRect&& rhs) KLAYGE_NOEXCEPT;
	template UIRect const Rect_T<uint32_t>::operator+() const KLAYGE_NOEXCEPT;
	template uint32_t Rect_T<uint32_t>::Width() const KLAYGE_NOEXCEPT;
	template uint32_t Rect_T<uint32_t>::Height() const KLAYGE_NOEXCEPT;
	template UISize const Rect_T<uint32_t>::Size() const KLAYGE_NOEXCEPT;
	template bool Rect_T<uint32_t>::IsEmpty() const KLAYGE_NOEXCEPT;
	template bool Rect_T<uint32_t>::operator==(UIRect const & rhs) const KLAYGE_NOEXCEPT;
	template bool Rect_T<uint32_t>::PtInRect(uint2 const & pt) const KLAYGE_NOEXCEPT;


	template <typename T>
	Rect_T<T>::Rect_T(T const * rhs) KLAYGE_NOEXCEPT
		: rect_(rhs)
	{
	}

	template <typename T>
	Rect_T<T>::Rect_T(Rect_T&& rhs) KLAYGE_NOEXCEPT
		: rect_(std::move(rhs.rect_))
	{
	}

	template <typename T>
	Rect_T<T>::Rect_T(T left, T top, T right, T bottom) KLAYGE_NOEXCEPT
	{
		this->left()	= left;
		this->top()		= top;
		this->right()	= right;
		this->bottom()	= bottom;
	}

	template <typename T>
	template <typename U>
	Rect_T<T> const & Rect_T<T>::operator+=(Vector_T<U, 2> const & rhs) KLAYGE_NOEXCEPT
	{
		this->left() += static_cast<T>(rhs.x());
		this->right() += static_cast<T>(rhs.x());
		this->top() += static_cast<T>(rhs.y());
		this->bottom() += static_cast<T>(rhs.y());
		return *this;
	}

	template <typename T>
	template <typename U>
	Rect_T<T> const & Rect_T<T>::operator-=(Vector_T<U, 2> const & rhs) KLAYGE_NOEXCEPT
	{
		this->left() -= static_cast<T>(rhs.x());
		this->right() -= static_cast<T>(rhs.x());
		this->top() -= static_cast<T>(rhs.y());
		this->bottom() -= static_cast<T>(rhs.y());
		return *this;
	}

	template <typename T>
	template <typename U>
	Rect_T<T> const & Rect_T<T>::operator+=(Rect_T<U> const & rhs) KLAYGE_NOEXCEPT
	{
		rect_ += Rect_T<T>(rhs).rect_;
		return *this;
	}

	template <typename T>
	template <typename U>
	Rect_T<T> const & Rect_T<T>::operator-=(Rect_T<U> const & rhs) KLAYGE_NOEXCEPT
	{
		rect_ -= Rect_T<T>(rhs).rect_;
		return *this;
	}

	template <typename T>
	template <typename U>
	Rect_T<T> const & Rect_T<T>::operator&=(Rect_T<U> const & rhs) KLAYGE_NOEXCEPT
	{
		this->left()	= std::max(this->left(),	static_cast<T>(rhs.left()));
		this->top()		= std::max(this->top(),		static_cast<T>(rhs.top()));
		this->right()	= std::min(this->right(),	static_cast<T>(rhs.right()));
		this->bottom()	= std::min(this->bottom(),	static_cast<T>(rhs.bottom()));
		return *this;
	}

	template <typename T>
	template <typename U>
	Rect_T<T> const & Rect_T<T>::operator|=(Rect_T<U> const & rhs) KLAYGE_NOEXCEPT
	{
		this->left()	= std::min(this->left(),	static_cast<T>(rhs.left()));
		this->top()		= std::min(this->top(),		static_cast<T>(rhs.top()));
		this->right()	= std::max(this->right(),	static_cast<T>(rhs.right()));
		this->bottom()	= std::max(this->bottom(),	static_cast<T>(rhs.bottom()));
		return *this;
	}

	template <typename T>
	Rect_T<T>& Rect_T<T>::operator=(Rect_T<T>&& rhs) KLAYGE_NOEXCEPT
	{
		rect_ = std::move(rhs.rect_);
		return *this;
	}

	template <typename T>
	Rect_T<T> const Rect_T<T>::operator+() const KLAYGE_NOEXCEPT
	{
		return *this;
	}

	template <typename T>
	Rect_T<T> const Rect_T<T>::operator-() const KLAYGE_NOEXCEPT
	{
		return Rect_T<T>(-this->left(), -this->top(), -this->right(), -this->bottom());
	}

	template <typename T>
	T Rect_T<T>::Width() const KLAYGE_NOEXCEPT
	{
		return this->right() - this->left();
	}

	template <typename T>
	T Rect_T<T>::Height() const KLAYGE_NOEXCEPT
	{
		return this->bottom() - this->top();
	}

	template <typename T>
	Size_T<T> const Rect_T<T>::Size() const KLAYGE_NOEXCEPT
	{
		return Size_T<T>(this->Width(), this->Height());
	}

	template <typename T>
	bool Rect_T<T>::IsEmpty() const KLAYGE_NOEXCEPT
	{
		return (this->left() == this->right()) && (this->top() == this->bottom());
	}

	template <typename T>
	bool Rect_T<T>::operator==(Rect_T<T> const & rhs) const KLAYGE_NOEXCEPT
	{
		return rect_ == rhs.rect_;
	}

	template <typename T>
	bool Rect_T<T>::PtInRect(Vector_T<T, 2> const & pt) const KLAYGE_NOEXCEPT
	{
		return MathLib::in_bound(pt.x(), this->left(), this->right())
			&& MathLib::in_bound(pt.y(), this->top(), this->bottom());
	}
}
