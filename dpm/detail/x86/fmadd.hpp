/*
 * Created by switchblade on 2023-01-15.
 */

#pragma once

#include "type.hpp"

namespace dpm
{
	namespace detail
	{
		[[maybe_unused]] [[nodiscard]] DPM_FORCEINLINE __m128 fmadd_sse(__m128 a, __m128 b, __m128 c) noexcept
		{
			return _mm_add_ps(_mm_mul_ps(a, b), c);
		}
		[[maybe_unused]] [[nodiscard]] DPM_FORCEINLINE __m128 fmsub_sse(__m128 a, __m128 b, __m128 c) noexcept
		{
			return _mm_sub_ps(_mm_mul_ps(a, b), c);
		}
		[[maybe_unused]] [[nodiscard]] DPM_FORCEINLINE __m128 fnmadd_sse(__m128 a, __m128 b, __m128 c) noexcept
		{
			return _mm_sub_ps(c, _mm_mul_ps(a, b));
		}
		[[maybe_unused]] [[nodiscard]] DPM_FORCEINLINE __m128 fnmsub_sse(__m128 a, __m128 b, __m128 c) noexcept
		{
			return _mm_sub_ps(_mm_setzero_ps(), fmadd_sse(a, b, c));
		}

		[[nodiscard]] DPM_FORCEINLINE __m128 fmadd(__m128 a, __m128 b, __m128 c) noexcept
		{
#ifdef DPM_HAS_FMA
			return _mm_fmadd_ps(a, b, c);
#else
			return fmadd_sse(a, b, c);
#endif
		}
		[[nodiscard]] DPM_FORCEINLINE __m128 fmsub(__m128 a, __m128 b, __m128 c) noexcept
		{
#ifdef DPM_HAS_FMA
			return _mm_fmsub_ps(a, b, c);
#else
			return fmsub_sse(a, b, c);
#endif
		}
		[[nodiscard]] DPM_FORCEINLINE __m128 fnmadd(__m128 a, __m128 b, __m128 c) noexcept
		{
#ifdef DPM_HAS_FMA
			return _mm_fnmadd_ps(a, b, c);
#else
			return fnmadd_sse(a, b, c);
#endif
		}
		[[nodiscard]] DPM_FORCEINLINE __m128 fnmsub(__m128 a, __m128 b, __m128 c) noexcept
		{
#ifdef DPM_HAS_FMA
			return _mm_fnmsub_ps(a, b, c);
#else
			return fnmsub_sse(a, b, c);
#endif
		}

#ifdef DPM_HAS_SSE2
		[[maybe_unused]] [[nodiscard]] DPM_FORCEINLINE __m128d fmadd_sse(__m128d a, __m128d b, __m128d c) noexcept
		{
			return _mm_add_pd(_mm_mul_pd(a, b), c);
		}
		[[maybe_unused]] [[nodiscard]] DPM_FORCEINLINE __m128d fmsub_sse(__m128d a, __m128d b, __m128d c) noexcept
		{
			return _mm_sub_pd(_mm_mul_pd(a, b), c);
		}
		[[maybe_unused]] [[nodiscard]] DPM_FORCEINLINE __m128d fnmadd_sse(__m128d a, __m128d b, __m128d c) noexcept
		{
			return _mm_sub_pd(c, _mm_mul_pd(a, b));
		}
		[[maybe_unused]] [[nodiscard]] DPM_FORCEINLINE __m128d fnmsub_sse(__m128d a, __m128d b, __m128d c) noexcept
		{
			return _mm_sub_pd(_mm_setzero_pd(), fmadd_sse(a, b, c));
		}

		[[nodiscard]] DPM_FORCEINLINE __m128d fmadd(__m128d a, __m128d b, __m128d c) noexcept
		{
#ifdef DPM_HAS_FMA
			return _mm_fmadd_pd(a, b, c);
#else
			return fmadd_sse(a, b, c);
#endif
		}
		[[nodiscard]] DPM_FORCEINLINE __m128d fmsub(__m128d a, __m128d b, __m128d c) noexcept
		{
#ifdef DPM_HAS_FMA
			return _mm_fmsub_pd(a, b, c);
#else
			return fmsub_sse(a, b, c);
#endif
		}
		[[nodiscard]] DPM_FORCEINLINE __m128d fnmadd(__m128d a, __m128d b, __m128d c) noexcept
		{
#ifdef DPM_HAS_FMA
			return _mm_fnmadd_pd(a, b, c);
#else
			return fnmadd_sse(a, b, c);
#endif
		}
		[[nodiscard]] DPM_FORCEINLINE __m128d fnmsub(__m128d a, __m128d b, __m128d c) noexcept
		{
#ifdef DPM_HAS_FMA
			return _mm_fnmsub_pd(a, b, c);
#else
			return fnmsub_sse(a, b, c);
#endif
		}
#endif
	}

	DPM_DECLARE_EXT_NAMESPACE
	{
		/** Returns a result of fused multiply-add operation on elements of \a a, \a b, and \a c. Equivalent to `a * b + c`. */
		template<std::floating_point T, std::size_t N, std::size_t A>
		[[nodiscard]] DPM_FORCEINLINE detail::x86_simd<T, N, A> fmadd(
				const detail::x86_simd<T, N, A> &a,
				const detail::x86_simd<T, N, A> &b,
				const detail::x86_simd<T, N, A> &c)
		noexcept requires detail::x86_overload_any<T, N, A>
		{
			detail::x86_simd<T, N, A> result = {};
			for (std::size_t i = 0; i < native_data_size_v<detail::x86_simd<T, N, A>>; ++i)
			{
				to_native_data(result)[i] = detail::fmadd(
						to_native_data(a)[i],
						to_native_data(b)[i],
						to_native_data(c)[i]
				);
			}
			return result;
		}
		/** Returns a result of fused multiply-sub operation on elements of \a a, \a b, and \a c. Equivalent to `a * b - c`. */
		template<std::floating_point T, std::size_t N, std::size_t A>
		[[nodiscard]] DPM_FORCEINLINE detail::x86_simd<T, N, A> fmsub(
				const detail::x86_simd<T, N, A> &a,
				const detail::x86_simd<T, N, A> &b,
				const detail::x86_simd<T, N, A> &c)
		noexcept requires detail::x86_overload_any<T, N, A>
		{
			detail::x86_simd<T, N, A> result = {};
			for (std::size_t i = 0; i < native_data_size_v<detail::x86_simd<T, N, A>>; ++i)
			{
				to_native_data(result)[i] = detail::fmsub(
						to_native_data(a)[i],
						to_native_data(b)[i],
						to_native_data(c)[i]
				);
			}
			return result;
		}
		/** Returns a result of fused negate-multiply-add operation on elements of \a a, \a b, and \a c. Equivalent to `-(a * b) + c`. */
		template<std::floating_point T, std::size_t N, std::size_t A>
		[[nodiscard]] DPM_FORCEINLINE detail::x86_simd<T, N, A> fnmadd(
				const detail::x86_simd<T, N, A> &a,
				const detail::x86_simd<T, N, A> &b,
				const detail::x86_simd<T, N, A> &c)
		noexcept requires detail::x86_overload_any<T, N, A>
		{
			detail::x86_simd<T, N, A> result = {};
			for (std::size_t i = 0; i < native_data_size_v<detail::x86_simd<T, N, A>>; ++i)
			{
				to_native_data(result)[i] = detail::fnmadd(
						to_native_data(a)[i],
						to_native_data(b)[i],
						to_native_data(c)[i]
				);
			}
			return result;
		}
		/** Returns a result of fused negate-multiply-sub operation on elements of \a a, \a b, and \a c. Equivalent to `-(a * b) - c`. */
		template<std::floating_point T, std::size_t N, std::size_t A>
		[[nodiscard]] DPM_FORCEINLINE detail::x86_simd<T, N, A> fnmsub(
				const detail::x86_simd<T, N, A> &a,
				const detail::x86_simd<T, N, A> &b,
				const detail::x86_simd<T, N, A> &c)
		noexcept requires detail::x86_overload_any<T, N, A>
		{
			detail::x86_simd<T, N, A> result = {};
			for (std::size_t i = 0; i < native_data_size_v<detail::x86_simd<T, N, A>>; ++i)
			{
				to_native_data(result)[i] = detail::fnmsub(
						to_native_data(a)[i],
						to_native_data(b)[i],
						to_native_data(c)[i]
				);
			}
			return result;
		}
	}

	/** Returns a result of fused multiply-add operation on elements of \a a, \a b, and \a c. Equivalent to `a * b + c`. */
	template<std::floating_point T, std::size_t N, std::size_t A>
	[[nodiscard]] DPM_FORCEINLINE detail::x86_simd<T, N, A> fma(
			const detail::x86_simd<T, N, A> &a,
			const detail::x86_simd<T, N, A> &b,
			const detail::x86_simd<T, N, A> &c)
	noexcept requires detail::x86_overload_any<T, N, A>
	{
		return ext::fmadd(a, b, c);
	}
}