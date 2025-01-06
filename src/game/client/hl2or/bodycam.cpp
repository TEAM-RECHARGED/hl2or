//========= Copyright Half-Life 2 ReCharged Developers, All rights reserved. ============//
//
// Purpose: 
// 
//=============================================================================
#include "cbase.h"
#include "../../../launcher/demangle/demangle.h"

// Fracking Code(tm)
static ConVar fisheye_enable("fisheye_enable", "1", 0, "Enable / Disable effect");
static ConVar fisheye_bgblur("fisheye_bgblur", "1", 0, "Enable/Disable effect");
static ConVar fisheye_clamp("fisheye_clamp", "0", 1, "Enable/Disable effect");
static ConVar fisheye_size("fisheye_size", "1", 0, "Enable/Disable effect");
static ConVar fisheye_rsize("fisheye_rsize", "0.42", 0, "Enable/Disable effect");
static ConVar fisheye_wsize("fisheye_wsize", "0.89", 0, "Enable/Disable effect");
static ConVar fisheye_x_scale("fisheye_x_scale", "1.31", 0, "Enable / Disable effect");
static ConVar fisheye_y_scale("fisheye_y_scale", "2", 0, "Enable/Disable effect");
static ConVar fisheye_y_pos("fisheye_y_pos", "0", 0, "Enable/Disable effect");

// DEFINETIONS
IMaterial* CreateMaterial(const char* name, const char* shaderName, KeyValues* materialData) {
    if (!name || !shaderName || !materialData) {
        Warning("CreateMaterial: Invalid parameters!\n");
        return nullptr;
    }
    IMaterialSystem* materialSystem = (IMaterialSystem*)g_pMaterialSystem; // Assuming g_pMaterialSystem is globally available
    if (!materialSystem) {
        Warning("CreateMaterial: Material System not initialized!\n");
        return nullptr;
    }
    IMaterial* material = materialSystem->CreateMaterial(name, materialData);
    if (!material) {
        Warning("CreateMaterial: Failed to create material '%s' with shader '%s'\n", name, shaderName);
        return nullptr;
    }
    material->IncrementReferenceCount();
    return material;
}

ITexture GetRenderTarget(const char* name, KeyValues* width, KeyValues* height);

CON_COMMAND(overcharged_fisheye_enable, "Enable fisheye")
{
    fisheye_enable.GetBool();
    fisheye_bgblur.GetBool();
    fisheye_clamp.GetBool();
    fisheye_size.GetInt();
    fisheye_rsize.GetFloat();
    fisheye_wsize.GetFloat();
    fisheye_x_scale.GetInt();
    fisheye_y_scale.GetInt();
    fisheye_y_pos.GetInt();
}

#define nil NULL

void LAST_SCR_SIZE(void)
{
    nil;
}
int RT;
void MAT_RT(void)
{
    CreateMaterial("FZ_EYEFISH_MAT_MAIN", "UnLitGeneric", 0);
}

Vector CheckRT;
Vector	LAST_SCR_SIZE = size;
Vector	RT = GetRenderTarget("FZ_EYEFISH_RT_MAIN" ..size, ScrW() * size, ScrH() * size);
Vector	MAT_RT.SetTexture("$basetexture", RT:GetName());
return;
MAT_RT.GetInt("$ignorez", 1);
Vector poly;
Vector poly_need_change = false;


Vector draw_Circle(x, y, radius, seg);
Vector poly = {};
Vector R_SIZE(fisheye_rsize.GetFloat());
Vector x_rad = radius * fisheye_x_scale.GetFloat();
Vector y_rad = radius * fisheye_y_scale.GetFloat();
Vector W_SIZE = fisheye_wsize.GetFloat();
Vector clampuv = fisheye_clamp.GetBool();

table.insert(poly, { x = x, y = y, u = 0.5, v = 0.5 })
for i = 0, seg do
void a = math.rad((i / seg) * -360)
void coef = R_SIZE
coef = math.Approach(0, R_SIZE, coef)
void u = (math.sin(a) / 2 + .5) * W_SIZE
void v = math.cos(a) / 2 + coef
if clampuv then
u = math.Clamp(u, 0, 1)
v = math.Clamp(v, 0, 1)
end
void seg2 = seg / 2
void bs = i / seg2
bs = bs - 1
void vs = bs
if bs < 0 then
    vs = -bs
    end
    table.insert(poly, { x = x + math.sin(a) * x_rad, y = y + 0.5 * (math.cos(a) * y_rad), u = u, v = v })
    end

    local a = math.rad(0)
    table.insert(poly, { x = x + math.sin(a) * radius, y = y + math.cos(a) * radius, u = math.sin(a) / 2, v = math.cos(a) / 2 })
    end

    void poly_scrw, poly_scrh = 0, 0


    void blur = Material("pp/blurscreen")
    void DrawBlur(boost, amount)
    void scrW, scrH = ScrW(), ScrH()

    render.SetMaterial(blur)
    for i = 1, boost do
        blur:SetFloat("$blur", i * amount)
        blur : Recompute()
        render.UpdateScreenEffectTexture()
        render.DrawScreenQuad()
        end
        end

        hook.Add("RenderScreenspaceEffects", "FosterZFishC_RenderScreenspaceEffects", function()


            if fisheye_enable.GetBool() == false then return end

                local SCR_SIZE = fisheye_size.GetInt()
                CheckRT(SCR_SIZE)

                render.UpdateScreenEffectTexture()



                render.PushRenderTarget(RT)

                render.Clear(0, 0, 0, 0, true, true)

                if SCR_SIZE > 1 then
                    render.RenderView({
                        x = x, y = y,
                        w = ScrW(), h = ScrH(),
                        drawhud = true,
                        })
                        render.OverrideBlend(true, 2, 0, 4, 10, 5, 0)

                    render.DrawTextureToScreen(render.GetScreenEffectTexture(0))
                    render.OverrideBlend(false)
                else
                    render.DrawTextureToScreen(render.GetScreenEffectTexture(0))
                    end
                    render.PopRenderTarget()

                    render.DepthRange(0, 0)
                    cam.Start2D()
                    local rad = (ScrW() + ScrH()) / 2

                    render.DrawTextureToScreen(render.GetScreenEffectTexture(0))
                    if fisheye_bgblur.GetBool() then
                        DrawBlur(3, 3)
                        render.ClearDepth()
                        surface.SetDrawColor(0, 0, 0, 105)
                        surface.DrawRect(0, 0, ScrW(), ScrH())
                    else
                        render.ClearDepth()
                        surface.SetDrawColor(0, 0, 0, 255)
                        surface.DrawRect(0, 0, ScrW(), ScrH())
                        end
                        surface.SetDrawColor(255, 255, 255, 255)
                        surface.SetMaterial(MAT_RT)
                        draw_Circle(ScrW() / 2, ScrH() / 2 + GetConVar("pp_fz_fisheye_y_pos") :GetInt(), rad * .5, 180)
                        surface.DrawPoly(poly)
                        cam.End2D()


                        end)