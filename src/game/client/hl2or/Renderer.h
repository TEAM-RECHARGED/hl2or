#pragma once

#include <memory>

#include "DXGIFactory.h"
#include "GraphicsCard.h"
#include "Device.h"
#include "Swapchain.h"
#include "MaterialBuilder.h"
#include "MeshLoader.h"
#include "TextureBuilder.h"
#include "Mesh.h"
#include "Material.h"
#include "BufferBuilder.h"
#include "windows.h"
#include "GraphicsError.h"

namespace BaghdadCore
{
	class Renderer final
	{
	public:
		class ImGuiRenderer final
		{
		public:
			void NewFrame() const noexcept;

			bool ForwardMessage(HWND hwnd, UINT uint, WPARAM wParam, LPARAM lParam) const noexcept;

			ImGuiRenderer(const Window& window, const Device& device);
			~ImGuiRenderer() noexcept;
		};

	public:
		void DrawMesh(const Mesh& mesh, const Material& material) const NOEXCEPT;
		void Blit(const Texture2D& source, const Texture2D& destination) const NOEXCEPT;
		void Blit(const Texture2D& source, const Texture2D& destination, unsigned int subResourceIndex) const NOEXCEPT;

		void SetViewport(const D3D11_VIEWPORT& viewport) noexcept;

		/// <summary>
		/// Sets the reneder texture on which to output.
		/// </summary>
		/// <param name="pRenderTexture">the render texture to set</param>
		/// <exception cref="GraphicsError">On Failure of creating depth texture</exception>
		/// <exception cref="BaghdadError">On Failure of creating depth texture</exception>
		void SetRenderTexture(std::unique_ptr<Texture2D>&& pRenderTexture);
		void ClearRenderTexture(const float color[4]) const NOEXCEPT;
		void RemoveRenderTexture() noexcept;

		Texture2D& GetRenderTexture() const noexcept;

		void ImGUI_NewFrame() const noexcept;
		void ImGUI_Render() const;
		bool IMGUI_ForwardMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) const noexcept;
		void InitializeImGUI(const Window& window) noexcept;

		Swapchain CreateSwapchain(const Window& window) const;

		TextureBuilder& GetTextureBuilder() const noexcept;
		MaterialBuilder& GetMaterialBuilder() const noexcept;
		MeshLoader& GetMeshLoader() const noexcept;
		BufferBuilder& GetBufferBuilder() const noexcept;

		/// <summary>
		/// Creates device on primary display adapter (graphics card).
		/// </summary>
		/// <exception cref="BaghdadError">If no Graphics capable adapter found.</exception>
		Renderer();

	private:
		DXGIFactory _factory;
		std::unique_ptr<GraphicsCard> _pCard;
		std::unique_ptr<Device> _pDevice;
		std::unique_ptr<Swapchain> _pSwapchain;

		std::unique_ptr<MaterialBuilder> _pMaterialBuilder;
		std::unique_ptr<MeshLoader> _pMeshLoader;
		std::unique_ptr<TextureBuilder> _pTextureBuilder;
		std::unique_ptr<BufferBuilder> _pBufferBuilder;

		std::unique_ptr<Texture2D> _pRenderTexture;
		std::unique_ptr<Texture2D> _pDepthTexture;

		Microsoft::WRL::ComPtr<ID3D11BlendState> _pBlendState_On;
		Microsoft::WRL::ComPtr<ID3D11BlendState> _pBlendState_Off;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> _pDepthState_On;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> _pDepthState_Off;

		Microsoft::WRL::ComPtr<ID3D11RasterizerState> _pRasterizerState_Cull_Back;
		Microsoft::WRL::ComPtr<ID3D11RasterizerState> _pRasterizerState_Cull_Front;
		Microsoft::WRL::ComPtr<ID3D11RasterizerState> _pRasterizerState_Cull_None;
		Microsoft::WRL::ComPtr<ID3D11RasterizerState> _pRasterizerState_Wireframe;
		D3D11_VIEWPORT _viewport = { 0 };

		std::unique_ptr<ImGuiRenderer> _pUIRenderer;
	};
}