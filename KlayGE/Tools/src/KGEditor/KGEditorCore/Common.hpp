#ifndef _KGEDITOR_CORE_COMMON_HPP
#define _KGEDITOR_CORE_COMMON_HPP

#pragma once

#ifdef KLAYGE_KGEDITOR_CORE_SOURCE		// Build dll
	#define KLAYGE_KGEDITOR_CORE_API KLAYGE_SYMBOL_EXPORT
#else							// Use dll
	#define KLAYGE_KGEDITOR_CORE_API KLAYGE_SYMBOL_IMPORT
#endif

#endif		// _KGEDITOR_CORE_COMMON_HPP
