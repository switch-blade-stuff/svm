/*
 * Created by switchblade on 2023-02-05.
 */

#pragma once

#include "mbase.hpp"

namespace dpm
{
	namespace detail
	{
		[[nodiscard]] DPM_FORCEINLINE __m128 rcp(__m128 x) noexcept { return _mm_rcp_ps(x); }
		[[nodiscard]] DPM_FORCEINLINE __m128 sqrt(__m128 x) noexcept { return _mm_sqrt_ps(x); }
		[[nodiscard]] DPM_FORCEINLINE __m128 rsqrt(__m128 x) noexcept { return _mm_rsqrt_ps(x); }

#ifdef DPM_HAS_SSE2
		[[nodiscard]] DPM_FORCEINLINE __m128d sqrt(__m128d x) noexcept { return _mm_sqrt_pd(x); }
#endif

#ifdef DPM_HAS_AVX
		[[nodiscard]] DPM_FORCEINLINE __m256 rcp(__m256 x) noexcept { return _mm256_rcp_ps(x); }
		[[nodiscard]] DPM_FORCEINLINE __m256 sqrt(__m256 x) noexcept { return _mm256_sqrt_ps(x); }
		[[nodiscard]] DPM_FORCEINLINE __m256 rsqrt(__m256 x) noexcept { return _mm256_rsqrt_ps(x); }

		[[nodiscard]] DPM_FORCEINLINE __m256d sqrt(__m256d x) noexcept { return _mm256_sqrt_pd(x); }
#endif
	}

	/** Calculates square root of elements in vector \a x, and returns the resulting vector. */
	template<std::floating_point T, std::size_t N, std::size_t A>
	[[nodiscard]] DPM_FORCEINLINE detail::x86_simd<T, N, A> sqrt(const detail::x86_simd<T, N, A> &x) noexcept requires detail::x86_overload_any<T, N, A>
	{
		detail::x86_simd<T, N, A> result = {};
		detail::vectorize([](auto &res, auto x) { res = detail::sqrt(x); }, result, x);
		return result;
	}

//	/** Raises elements of vector \a x to power specified by elements of vector \a p, and returns the resulting vector. */
//	template<std::floating_point T, std::size_t N, std::size_t A>
//	[[nodiscard]] DPM_FORCEINLINE detail::x86_simd<T, N, A> pow(const detail::x86_simd<T, N, A> &x, const detail::x86_simd<T, N, A> &p) noexcept requires detail::x86_overload_any<T, N, A>
//	{
//	}
//	/** Calculates cube root of elements in vector \a x, and returns the resulting vector. */
//	template<std::floating_point T, std::size_t N, std::size_t A>
//	[[nodiscard]] DPM_FORCEINLINE detail::x86_simd<T, N, A> cbrt(const detail::x86_simd<T, N, A> &x) noexcept requires detail::x86_overload_any<T, N, A>
//	{
//	}
//	/** Calculates square root of the sum of elements in vectors \a a and \a b without causing over or underflow, and returns the resulting vector. */
//	template<std::floating_point T, std::size_t N, std::size_t A>
//	[[nodiscard]] DPM_FORCEINLINE detail::x86_simd<T, N, A> hypot(const detail::x86_simd<T, N, A> &a, const detail::x86_simd<T, N, A> &b) noexcept requires detail::x86_overload_any<T, N, A>
//	{
//	}

	DPM_DECLARE_EXT_NAMESPACE
	{
		/** Calculates reciprocal of elements in vector \a x, and returns the resulting vector. */
		template<std::size_t N, std::size_t A>
		[[nodiscard]] DPM_FORCEINLINE detail::x86_simd<float, N, A> rcp(const detail::x86_simd<float, N, A> &x) noexcept requires detail::x86_overload_any<float, N, A>
		{
			detail::x86_simd<float, N, A> result = {};
			detail::vectorize([](auto &res, auto x) { res = detail::rcp(x); }, result, x);
			return result;
		}
		/** Calculates reciprocal square root of elements in vector \a x, and returns the resulting vector. */
		template<std::size_t N, std::size_t A>
		[[nodiscard]] DPM_FORCEINLINE detail::x86_simd<float, N, A> rsqrt(const detail::x86_simd<float, N, A> &x) noexcept requires detail::x86_overload_any<float, N, A>
		{
			detail::x86_simd<float, N, A> result = {};
			detail::vectorize([](auto &res, auto x) { res = detail::rsqrt(x); }, result, x);
			return result;
		}
	}
}