/**
 * @file WindowWinRT.cpp
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

#ifdef KLAYGE_PLATFORM_WINDOWS_RUNTIME

#include <KFL/Math.hpp>
#include <KFL/Util.hpp>
#include <KFL/ThrowErr.hpp>

#include <windows.graphics.display.h>
#include <wrl/client.h>
#include <wrl/wrappers/corewrappers.h>

#include <KlayGE/Window.hpp>

using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Graphics::Display;
using namespace ABI::Windows::UI::Core;
using namespace ABI::Windows::UI::Input;
#if (_WIN32_WINNT >= _WIN32_WINNT_WIN10)
using namespace ABI::Windows::UI::ViewManagement;
#endif
using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;

namespace KlayGE
{
	Window::Window(std::string const & name, RenderSettings const & settings)
		: active_(false), ready_(false), closed_(false),
			dpi_scale_(1), win_rotation_(WR_Identity)
	{
		Convert(wname_, name);

		pointer_id_map_.fill(0);

#if (_WIN32_WINNT >= _WIN32_WINNT_WIN10)
		width_ = settings.width;
		height_ = settings.height;
		full_screen_ = settings.full_screen;
#else
		KFL_UNUSED(settings);
#endif
	}

	Window::Window(std::string const & name, RenderSettings const & settings, void* native_wnd)
		: active_(false), ready_(false), closed_(false),
			dpi_scale_(1), win_rotation_(WR_Identity)
	{
		KFL_UNUSED(native_wnd);

		Convert(wname_, name);

		pointer_id_map_.fill(0);

#if (_WIN32_WINNT >= _WIN32_WINNT_WIN10)
		width_ = settings.width;
		height_ = settings.height;
		full_screen_ = settings.full_screen;
#else
		KFL_UNUSED(settings);
#endif
	}

	Window::~Window()
	{
	}

	void Window::SetWindow(std::shared_ptr<ABI::Windows::UI::Core::ICoreWindow> const & window)
	{
		wnd_ = window;

		left_ = 0;
		top_ = 0;
		
		this->DetectsDPI();
		this->DetectsOrientation();

#if (_WIN32_WINNT >= _WIN32_WINNT_WIN10)
		ComPtr<IApplicationViewStatics> app_view_stat;
		GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_ViewManagement_ApplicationView).Get(), &app_view_stat);

		ComPtr<IApplicationViewStatics2> app_view_stat2;
		app_view_stat.As(&app_view_stat2);

		ComPtr<IApplicationView> app_view;
		app_view_stat2->GetForCurrentView(&app_view);

		app_view->put_Title(HStringReference(wname_.c_str()).Get());

		ComPtr<IApplicationViewStatics3> app_view_stat3;
		app_view_stat.As(&app_view_stat3);

		ABI::Windows::Foundation::Size size;
		size.Width = static_cast<float>(width_ / dpi_scale_);
		size.Height = static_cast<float>(height_ / dpi_scale_);
		app_view_stat3->put_PreferredLaunchViewSize(size);
		app_view_stat3->put_PreferredLaunchWindowingMode(ApplicationViewWindowingMode_PreferredLaunchViewSize);
#endif

		ABI::Windows::Foundation::Rect rc;
		wnd_->get_Bounds(&rc);
		width_ = static_cast<uint32_t>(rc.Width * dpi_scale_ + 0.5f);
		height_ = static_cast<uint32_t>(rc.Height * dpi_scale_ + 0.5f);

		ready_ = true;
	}

	void Window::DetectsDPI()
	{
#if (_WIN32_WINNT >= _WIN32_WINNT_WINBLUE)
		ComPtr<IDisplayInformationStatics> disp_info_stat;
		TIF(GetActivationFactory(HStringReference(RuntimeClass_Windows_Graphics_Display_DisplayInformation).Get(),
			&disp_info_stat));

		ComPtr<IDisplayInformation> disp_info;
		TIF(disp_info_stat->GetForCurrentView(&disp_info));

		float dpi;
		TIF(disp_info->get_LogicalDpi(&dpi));
#else
		ComPtr<IDisplayPropertiesStatics> disp_prop;
		TIF(GetActivationFactory(HStringReference(RuntimeClass_Windows_Graphics_Display_DisplayProperties).Get(),
			&disp_prop));

		float dpi;
		TIF(disp_prop->get_LogicalDpi(&dpi));
#endif

		dpi_scale_ = dpi / 96;
	}

	void Window::DetectsOrientation()
	{
#if (_WIN32_WINNT >= _WIN32_WINNT_WINBLUE)
		ComPtr<IDisplayInformationStatics> disp_info_stat;
		TIF(GetActivationFactory(HStringReference(RuntimeClass_Windows_Graphics_Display_DisplayInformation).Get(),
			&disp_info_stat));

		ComPtr<IDisplayInformation> disp_info;
		TIF(disp_info_stat->GetForCurrentView(&disp_info));

		DisplayOrientations native_orientation;
		TIF(disp_info->get_NativeOrientation(&native_orientation));

		DisplayOrientations curr_orientation;
		TIF(disp_info->get_CurrentOrientation(&curr_orientation));
#else
		ComPtr<IDisplayPropertiesStatics> disp_prop;
		TIF(GetActivationFactory(HStringReference(RuntimeClass_Windows_Graphics_Display_DisplayProperties).Get(),
			&disp_prop));

		DisplayOrientations orientation;
		TIF(disp_prop->get_CurrentOrientation(&orientation));
#endif

		win_rotation_ = WR_Unspecified;

		switch (native_orientation)
		{
		case DisplayOrientations_Landscape:
			switch (curr_orientation)
			{
			case DisplayOrientations_Landscape:
				win_rotation_ = WR_Identity;
				break;

			case DisplayOrientations_Portrait:
				win_rotation_ = WR_Rotate270;
				break;

			case DisplayOrientations_LandscapeFlipped:
				win_rotation_ = WR_Rotate180;
				break;

			case DisplayOrientations_PortraitFlipped:
				win_rotation_ = WR_Rotate90;
				break;

			default:
				BOOST_ASSERT(false);
				break;
			}
			break;

		case DisplayOrientations_Portrait:
			switch (curr_orientation)
			{
			case DisplayOrientations_Landscape:
				win_rotation_ = WR_Rotate90;
				break;

			case DisplayOrientations_Portrait:
				win_rotation_ = WR_Identity;
				break;

			case DisplayOrientations_LandscapeFlipped:
				win_rotation_ = WR_Rotate270;
				break;

			case DisplayOrientations_PortraitFlipped:
				win_rotation_ = WR_Rotate180;
				break;

			default:
				BOOST_ASSERT(false);
				break;
			}
			break;

		default:
			BOOST_ASSERT(false);
			break;
		}
	}

	bool Window::FullScreen(bool fs)
	{
#if (_WIN32_WINNT >= _WIN32_WINNT_WIN10)
		ComPtr<IApplicationViewStatics> app_view_stat;
		GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_ViewManagement_ApplicationView).Get(), &app_view_stat);

		ComPtr<IApplicationViewStatics2> app_view_stat2;
		app_view_stat.As(&app_view_stat2);

		ComPtr<IApplicationView> app_view;
		app_view_stat2->GetForCurrentView(&app_view);

		ComPtr<IApplicationViewStatics3> app_view_stat3;
		app_view_stat.As(&app_view_stat3);

		ComPtr<IApplicationView3> app_view3;
		app_view.As(&app_view3);

		boolean success;
		if (fs)
		{
			app_view3->TryEnterFullScreenMode(&success);
			if (success)
			{
				app_view_stat3->put_PreferredLaunchWindowingMode(ApplicationViewWindowingMode_FullScreen);
			}
		}
		else
		{
			success = true;
			app_view3->ExitFullScreenMode();
			app_view_stat3->put_PreferredLaunchWindowingMode(ApplicationViewWindowingMode_PreferredLaunchViewSize);
		}

		return success ? true : false;
#else
		KFL_UNUSED(fs);
		return false;
#endif
	}

	void Window::OnActivated()
	{
		if (full_screen_)
		{
			this->FullScreen(true);
		}
	}

	void Window::OnSizeChanged(IWindowSizeChangedEventArgs* args)
	{
		ABI::Windows::Foundation::Size size;
		args->get_Size(&size);

		active_ = true;

		width_ = static_cast<uint32_t>(size.Width * dpi_scale_ + 0.5f);
		height_ = static_cast<uint32_t>(size.Height * dpi_scale_ + 0.5f);

		this->OnSize()(*this, true);
	}

	void Window::OnVisibilityChanged(IVisibilityChangedEventArgs* args)
	{
		boolean vis;
		TIF(args->get_Visible(&vis));

		active_ = vis ? true : false;
		this->OnActive()(*this, active_);
	}

	void Window::OnClosed()
	{
		this->OnClose()(*this);

		active_ = false;
		ready_ = false;
		closed_ = true;
	}

	void Window::OnKeyDown(IKeyEventArgs* args)
	{
		ABI::Windows::System::VirtualKey vk;
		TIF(args->get_VirtualKey(&vk));
		if (vk < 256)
		{
			this->OnKeyDown()(*this, vk);
		}
	}

	void Window::OnKeyUp(IKeyEventArgs* args)
	{
		ABI::Windows::System::VirtualKey vk;
		TIF(args->get_VirtualKey(&vk));
		if (vk < 256)
		{
			this->OnKeyUp()(*this, vk);
		}
	}

	void Window::OnPointerPressed(IPointerEventArgs* args)
	{
		ComPtr<IPointerPoint> point;
		TIF(args->get_CurrentPoint(&point));

		UINT32 pid;
		TIF(point->get_PointerId(&pid));

		uint32_t conv_id = 0;
		for (size_t i = 0; i < pointer_id_map_.size(); ++i)
		{
			if (0 == pointer_id_map_[i])
			{
				conv_id = static_cast<uint32_t>(i + 1);
				pointer_id_map_[i] = pid;
				break;
			}
		}

		Point position;
		TIF(point->get_Position(&position));

		this->OnPointerDown()(*this, int2(static_cast<int>(position.X * dpi_scale_), static_cast<int>(position.Y * dpi_scale_)), conv_id);
	}

	void Window::OnPointerReleased(IPointerEventArgs* args)
	{
		ComPtr<IPointerPoint> point;
		TIF(args->get_CurrentPoint(&point));

		UINT32 pid;
		TIF(point->get_PointerId(&pid));

		uint32_t conv_id = 0;
		for (size_t i = 0; i < pointer_id_map_.size(); ++i)
		{
			if (pid == pointer_id_map_[i])
			{
				conv_id = static_cast<uint32_t>(i + 1);
				pointer_id_map_[i] = 0;
				break;
			}
		}

		Point position;
		TIF(point->get_Position(&position));

		this->OnPointerUp()(*this, int2(static_cast<int>(position.X * dpi_scale_), static_cast<int>(position.Y * dpi_scale_)), conv_id);
	}

	void Window::OnPointerMoved(IPointerEventArgs* args)
	{
		ComPtr<IPointerPoint> point;
		TIF(args->get_CurrentPoint(&point));

		UINT32 pid;
		TIF(point->get_PointerId(&pid));

		uint32_t conv_id = 0;
		for (size_t i = 0; i < pointer_id_map_.size(); ++i)
		{
			if (pid == pointer_id_map_[i])
			{
				conv_id = static_cast<uint32_t>(i + 1);
				break;
			}
		}

		Point position;
		TIF(point->get_Position(&position));
		boolean contact;
		TIF(point->get_IsInContact(&contact));

		this->OnPointerUpdate()(*this, int2(static_cast<int>(position.X * dpi_scale_), static_cast<int>(position.Y * dpi_scale_)),
			conv_id, contact ? true : false);
	}

	void Window::OnPointerWheelChanged(IPointerEventArgs* args)
	{
		ComPtr<IPointerPoint> point;
		TIF(args->get_CurrentPoint(&point));

		UINT32 pid;
		TIF(point->get_PointerId(&pid));

		uint32_t conv_id = 0;
		for (size_t i = 0; i < pointer_id_map_.size(); ++i)
		{
			if (pid == pointer_id_map_[i])
			{
				conv_id = static_cast<uint32_t>(i + 1);
				break;
			}
		}

		Point position;
		TIF(point->get_Position(&position));
		ComPtr<IPointerPointProperties> properties;
		TIF(point->get_Properties(&properties));
		INT32 wheel;
		TIF(properties->get_MouseWheelDelta(&wheel));

		this->OnPointerWheel()(*this, int2(static_cast<int>(position.X * dpi_scale_), static_cast<int>(position.Y * dpi_scale_)),
			conv_id, wheel);
	}

	void Window::OnDpiChanged()
	{
		this->DetectsDPI();
	}

	void Window::OnOrientationChanged()
	{
		this->DetectsOrientation();

		this->OnSize()(*this, true);
	}

	void Window::OnDisplayContentsInvalidated()
	{
		// TODO
	}
}

#endif
