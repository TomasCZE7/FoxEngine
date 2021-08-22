set(PROJECT_NAME FoxEngine)

################################################################################
# Source groups
################################################################################
set(src
    "src/fepch.cpp"
    "src/fepch.h"
    "src/FoxEngine.h"
)
source_group("src" FILES ${src})

set(src__FoxEngine__Core
    "src/FoxEngine/Core/Application.cpp"
    "src/FoxEngine/Core/Application.h"
    "src/FoxEngine/Core/Core.h"
    "src/FoxEngine/Core/EntryPoint.h"
    "src/FoxEngine/Core/Input.h"
    "src/FoxEngine/Core/KeyCodes.h"
    "src/FoxEngine/Core/Layer.cpp"
    "src/FoxEngine/Core/Layer.h"
    "src/FoxEngine/Core/LayerStack.cpp"
    "src/FoxEngine/Core/LayerStack.h"
    "src/FoxEngine/Core/Log.cpp"
    "src/FoxEngine/Core/Log.h"
    "src/FoxEngine/Core/MouseButtonCodes.h"
    "src/FoxEngine/Core/TimeStep.h"
    "src/FoxEngine/Core/Window.h"
)
source_group("src\\FoxEngine\\Core" FILES ${src__FoxEngine__Core})

set(src__FoxEngine__Debug
    "src/FoxEngine/Debug/Instrumentor.h"
)
source_group("src\\FoxEngine\\Debug" FILES ${src__FoxEngine__Debug})

set(src__FoxEngine__Event
    "src/FoxEngine/Event/ApplicationEvent.h"
    "src/FoxEngine/Event/Event.h"
    "src/FoxEngine/Event/KeyboardEvent.h"
    "src/FoxEngine/Event/MouseEvent.h"
    "src/FoxEngine/Event/WindowEvent.h"
)
source_group("src\\FoxEngine\\Event" FILES ${src__FoxEngine__Event})

set(src__FoxEngine__ImGui
    "src/FoxEngine/ImGui/ImGuiBuild.cpp"
    "src/FoxEngine/ImGui/ImGuiLayer.cpp"
    "src/FoxEngine/ImGui/ImGuiLayer.h"
)
source_group("src\\FoxEngine\\ImGui" FILES ${src__FoxEngine__ImGui})

set(src__FoxEngine__Platform__OpenGL
    "src/FoxEngine/Platform/OpenGL/OpenGLBuffer.cpp"
    "src/FoxEngine/Platform/OpenGL/OpenGLBuffer.h"
    "src/FoxEngine/Platform/OpenGL/OpenGLContext.cpp"
    "src/FoxEngine/Platform/OpenGL/OpenGLContext.h"
    "src/FoxEngine/Platform/OpenGL/OpenGLFrameBuffer.cpp"
    "src/FoxEngine/Platform/OpenGL/OpenGLFrameBuffer.h"
    "src/FoxEngine/Platform/OpenGL/OpenGLRendererAPI.cpp"
    "src/FoxEngine/Platform/OpenGL/OpenGLRendererAPI.h"
    "src/FoxEngine/Platform/OpenGL/OpenGLShader.cpp"
    "src/FoxEngine/Platform/OpenGL/OpenGLShader.h"
    "src/FoxEngine/Platform/OpenGL/OpenGLTexture.cpp"
    "src/FoxEngine/Platform/OpenGL/OpenGLTexture.h"
    "src/FoxEngine/Platform/OpenGL/OpenGLVertexArray.cpp"
    "src/FoxEngine/Platform/OpenGL/OpenGLVertexArray.h"
)
source_group("src\\FoxEngine\\Platform\\OpenGL" FILES ${src__FoxEngine__Platform__OpenGL})

set(src__FoxEngine__Platform__Windows
    "src/FoxEngine/Platform/Windows/WindowsInput.cpp"
    "src/FoxEngine/Platform/Windows/WindowsWindow.cpp"
    "src/FoxEngine/Platform/Windows/WindowsWindow.h"
)
source_group("src\\FoxEngine\\Platform\\Windows" FILES ${src__FoxEngine__Platform__Windows})

set(src__FoxEngine__Renderer
    "src/FoxEngine/Renderer/Buffer.cpp"
    "src/FoxEngine/Renderer/Buffer.h"
    "src/FoxEngine/Renderer/FrameBuffer.cpp"
    "src/FoxEngine/Renderer/FrameBuffer.h"
    "src/FoxEngine/Renderer/GraphicsContext.h"
    "src/FoxEngine/Renderer/OrthographicCamera.cpp"
    "src/FoxEngine/Renderer/OrthographicCamera.h"
    "src/FoxEngine/Renderer/OrthographicCameraController.cpp"
    "src/FoxEngine/Renderer/OrthographicCameraController.h"
    "src/FoxEngine/Renderer/RenderCommand.cpp"
    "src/FoxEngine/Renderer/RenderCommand.h"
    "src/FoxEngine/Renderer/Renderer.cpp"
    "src/FoxEngine/Renderer/Renderer.h"
    "src/FoxEngine/Renderer/Renderer2D.cpp"
    "src/FoxEngine/Renderer/Renderer2D.h"
    "src/FoxEngine/Renderer/RendererAPI.cpp"
    "src/FoxEngine/Renderer/RendererAPI.h"
    "src/FoxEngine/Renderer/Shader.cpp"
    "src/FoxEngine/Renderer/Shader.h"
    "src/FoxEngine/Renderer/SubTexture2D.cpp"
    "src/FoxEngine/Renderer/SubTexture2D.h"
    "src/FoxEngine/Renderer/Texture.cpp"
    "src/FoxEngine/Renderer/Texture.h"
    "src/FoxEngine/Renderer/VertexArray.cpp"
    "src/FoxEngine/Renderer/VertexArray.h"
        src/FoxEngine/Renderer/Camera.cpp src/FoxEngine/Renderer/Camera.h)
source_group("src\\FoxEngine\\Renderer" FILES ${src__FoxEngine__Renderer})

set(src__FoxEngine__Scene
        "src/FoxEngine/Scene/Components.h"
        "src/FoxEngine/Scene/Entity.cpp"
        "src/FoxEngine/Scene/Entity.h"
        "src/FoxEngine/Scene/Scene.cpp"
        "src/FoxEngine/Scene/Scene.h"
        src/FoxEngine/Scene/SceneCamera.cpp src/FoxEngine/Scene/SceneCamera.h src/FoxEngine/Scene/ScriptableEntity.cpp src/FoxEngine/Scene/ScriptableEntity.h)
source_group("src\\FoxEngine\\Scene" FILES ${src__FoxEngine__Scene})

set(vendor__glm__glm
    "vendor/glm/glm/common.hpp"
    "vendor/glm/glm/exponential.hpp"
    "vendor/glm/glm/ext.hpp"
    "vendor/glm/glm/fwd.hpp"
    "vendor/glm/glm/geometric.hpp"
    "vendor/glm/glm/glm.hpp"
    "vendor/glm/glm/integer.hpp"
    "vendor/glm/glm/mat2x2.hpp"
    "vendor/glm/glm/mat2x3.hpp"
    "vendor/glm/glm/mat2x4.hpp"
    "vendor/glm/glm/mat3x2.hpp"
    "vendor/glm/glm/mat3x3.hpp"
    "vendor/glm/glm/mat3x4.hpp"
    "vendor/glm/glm/mat4x2.hpp"
    "vendor/glm/glm/mat4x3.hpp"
    "vendor/glm/glm/mat4x4.hpp"
    "vendor/glm/glm/matrix.hpp"
    "vendor/glm/glm/packing.hpp"
    "vendor/glm/glm/trigonometric.hpp"
    "vendor/glm/glm/vec2.hpp"
    "vendor/glm/glm/vec3.hpp"
    "vendor/glm/glm/vec4.hpp"
    "vendor/glm/glm/vector_relational.hpp"
)
source_group("vendor\\glm\\glm" FILES ${vendor__glm__glm})

set(vendor__glm__glm__detail
    "vendor/glm/glm/detail/_features.hpp"
    "vendor/glm/glm/detail/_fixes.hpp"
    "vendor/glm/glm/detail/_noise.hpp"
    "vendor/glm/glm/detail/_swizzle.hpp"
    "vendor/glm/glm/detail/_swizzle_func.hpp"
    "vendor/glm/glm/detail/_vectorize.hpp"
    "vendor/glm/glm/detail/compute_common.hpp"
    "vendor/glm/glm/detail/compute_vector_relational.hpp"
    "vendor/glm/glm/detail/func_common.inl"
    "vendor/glm/glm/detail/func_common_simd.inl"
    "vendor/glm/glm/detail/func_exponential.inl"
    "vendor/glm/glm/detail/func_exponential_simd.inl"
    "vendor/glm/glm/detail/func_geometric.inl"
    "vendor/glm/glm/detail/func_geometric_simd.inl"
    "vendor/glm/glm/detail/func_integer.inl"
    "vendor/glm/glm/detail/func_integer_simd.inl"
    "vendor/glm/glm/detail/func_matrix.inl"
    "vendor/glm/glm/detail/func_matrix_simd.inl"
    "vendor/glm/glm/detail/func_packing.inl"
    "vendor/glm/glm/detail/func_packing_simd.inl"
    "vendor/glm/glm/detail/func_trigonometric.inl"
    "vendor/glm/glm/detail/func_trigonometric_simd.inl"
    "vendor/glm/glm/detail/func_vector_relational.inl"
    "vendor/glm/glm/detail/func_vector_relational_simd.inl"
    "vendor/glm/glm/detail/qualifier.hpp"
    "vendor/glm/glm/detail/setup.hpp"
    "vendor/glm/glm/detail/type_float.hpp"
    "vendor/glm/glm/detail/type_half.hpp"
    "vendor/glm/glm/detail/type_half.inl"
    "vendor/glm/glm/detail/type_mat2x2.hpp"
    "vendor/glm/glm/detail/type_mat2x2.inl"
    "vendor/glm/glm/detail/type_mat2x3.hpp"
    "vendor/glm/glm/detail/type_mat2x3.inl"
    "vendor/glm/glm/detail/type_mat2x4.hpp"
    "vendor/glm/glm/detail/type_mat2x4.inl"
    "vendor/glm/glm/detail/type_mat3x2.hpp"
    "vendor/glm/glm/detail/type_mat3x2.inl"
    "vendor/glm/glm/detail/type_mat3x3.hpp"
    "vendor/glm/glm/detail/type_mat3x3.inl"
    "vendor/glm/glm/detail/type_mat3x4.hpp"
    "vendor/glm/glm/detail/type_mat3x4.inl"
    "vendor/glm/glm/detail/type_mat4x2.hpp"
    "vendor/glm/glm/detail/type_mat4x2.inl"
    "vendor/glm/glm/detail/type_mat4x3.hpp"
    "vendor/glm/glm/detail/type_mat4x3.inl"
    "vendor/glm/glm/detail/type_mat4x4.hpp"
    "vendor/glm/glm/detail/type_mat4x4.inl"
    "vendor/glm/glm/detail/type_mat4x4_simd.inl"
    "vendor/glm/glm/detail/type_quat.hpp"
    "vendor/glm/glm/detail/type_quat.inl"
    "vendor/glm/glm/detail/type_quat_simd.inl"
    "vendor/glm/glm/detail/type_vec1.hpp"
    "vendor/glm/glm/detail/type_vec1.inl"
    "vendor/glm/glm/detail/type_vec2.hpp"
    "vendor/glm/glm/detail/type_vec2.inl"
    "vendor/glm/glm/detail/type_vec3.hpp"
    "vendor/glm/glm/detail/type_vec3.inl"
    "vendor/glm/glm/detail/type_vec4.hpp"
    "vendor/glm/glm/detail/type_vec4.inl"
    "vendor/glm/glm/detail/type_vec4_simd.inl"
)
source_group("vendor\\glm\\glm\\detail" FILES ${vendor__glm__glm__detail})

set(vendor__glm__glm__ext
    "vendor/glm/glm/ext/matrix_clip_space.hpp"
    "vendor/glm/glm/ext/matrix_clip_space.inl"
    "vendor/glm/glm/ext/matrix_common.hpp"
    "vendor/glm/glm/ext/matrix_common.inl"
    "vendor/glm/glm/ext/matrix_double2x2.hpp"
    "vendor/glm/glm/ext/matrix_double2x2_precision.hpp"
    "vendor/glm/glm/ext/matrix_double2x3.hpp"
    "vendor/glm/glm/ext/matrix_double2x3_precision.hpp"
    "vendor/glm/glm/ext/matrix_double2x4.hpp"
    "vendor/glm/glm/ext/matrix_double2x4_precision.hpp"
    "vendor/glm/glm/ext/matrix_double3x2.hpp"
    "vendor/glm/glm/ext/matrix_double3x2_precision.hpp"
    "vendor/glm/glm/ext/matrix_double3x3.hpp"
    "vendor/glm/glm/ext/matrix_double3x3_precision.hpp"
    "vendor/glm/glm/ext/matrix_double3x4.hpp"
    "vendor/glm/glm/ext/matrix_double3x4_precision.hpp"
    "vendor/glm/glm/ext/matrix_double4x2.hpp"
    "vendor/glm/glm/ext/matrix_double4x2_precision.hpp"
    "vendor/glm/glm/ext/matrix_double4x3.hpp"
    "vendor/glm/glm/ext/matrix_double4x3_precision.hpp"
    "vendor/glm/glm/ext/matrix_double4x4.hpp"
    "vendor/glm/glm/ext/matrix_double4x4_precision.hpp"
    "vendor/glm/glm/ext/matrix_float2x2.hpp"
    "vendor/glm/glm/ext/matrix_float2x2_precision.hpp"
    "vendor/glm/glm/ext/matrix_float2x3.hpp"
    "vendor/glm/glm/ext/matrix_float2x3_precision.hpp"
    "vendor/glm/glm/ext/matrix_float2x4.hpp"
    "vendor/glm/glm/ext/matrix_float2x4_precision.hpp"
    "vendor/glm/glm/ext/matrix_float3x2.hpp"
    "vendor/glm/glm/ext/matrix_float3x2_precision.hpp"
    "vendor/glm/glm/ext/matrix_float3x3.hpp"
    "vendor/glm/glm/ext/matrix_float3x3_precision.hpp"
    "vendor/glm/glm/ext/matrix_float3x4.hpp"
    "vendor/glm/glm/ext/matrix_float3x4_precision.hpp"
    "vendor/glm/glm/ext/matrix_float4x2.hpp"
    "vendor/glm/glm/ext/matrix_float4x2_precision.hpp"
    "vendor/glm/glm/ext/matrix_float4x3.hpp"
    "vendor/glm/glm/ext/matrix_float4x3_precision.hpp"
    "vendor/glm/glm/ext/matrix_float4x4.hpp"
    "vendor/glm/glm/ext/matrix_float4x4_precision.hpp"
    "vendor/glm/glm/ext/matrix_int2x2.hpp"
    "vendor/glm/glm/ext/matrix_int2x2_sized.hpp"
    "vendor/glm/glm/ext/matrix_int2x3.hpp"
    "vendor/glm/glm/ext/matrix_int2x3_sized.hpp"
    "vendor/glm/glm/ext/matrix_int2x4.hpp"
    "vendor/glm/glm/ext/matrix_int2x4_sized.hpp"
    "vendor/glm/glm/ext/matrix_int3x2.hpp"
    "vendor/glm/glm/ext/matrix_int3x2_sized.hpp"
    "vendor/glm/glm/ext/matrix_int3x3.hpp"
    "vendor/glm/glm/ext/matrix_int3x3_sized.hpp"
    "vendor/glm/glm/ext/matrix_int3x4.hpp"
    "vendor/glm/glm/ext/matrix_int3x4_sized.hpp"
    "vendor/glm/glm/ext/matrix_int4x2.hpp"
    "vendor/glm/glm/ext/matrix_int4x2_sized.hpp"
    "vendor/glm/glm/ext/matrix_int4x3.hpp"
    "vendor/glm/glm/ext/matrix_int4x3_sized.hpp"
    "vendor/glm/glm/ext/matrix_int4x4.hpp"
    "vendor/glm/glm/ext/matrix_int4x4_sized.hpp"
    "vendor/glm/glm/ext/matrix_integer.hpp"
    "vendor/glm/glm/ext/matrix_integer.inl"
    "vendor/glm/glm/ext/matrix_projection.hpp"
    "vendor/glm/glm/ext/matrix_projection.inl"
    "vendor/glm/glm/ext/matrix_relational.hpp"
    "vendor/glm/glm/ext/matrix_relational.inl"
    "vendor/glm/glm/ext/matrix_transform.hpp"
    "vendor/glm/glm/ext/matrix_transform.inl"
    "vendor/glm/glm/ext/matrix_uint2x2.hpp"
    "vendor/glm/glm/ext/matrix_uint2x2_sized.hpp"
    "vendor/glm/glm/ext/matrix_uint2x3.hpp"
    "vendor/glm/glm/ext/matrix_uint2x3_sized.hpp"
    "vendor/glm/glm/ext/matrix_uint2x4.hpp"
    "vendor/glm/glm/ext/matrix_uint2x4_sized.hpp"
    "vendor/glm/glm/ext/matrix_uint3x2.hpp"
    "vendor/glm/glm/ext/matrix_uint3x2_sized.hpp"
    "vendor/glm/glm/ext/matrix_uint3x3.hpp"
    "vendor/glm/glm/ext/matrix_uint3x3_sized.hpp"
    "vendor/glm/glm/ext/matrix_uint3x4.hpp"
    "vendor/glm/glm/ext/matrix_uint3x4_sized.hpp"
    "vendor/glm/glm/ext/matrix_uint4x2.hpp"
    "vendor/glm/glm/ext/matrix_uint4x2_sized.hpp"
    "vendor/glm/glm/ext/matrix_uint4x3.hpp"
    "vendor/glm/glm/ext/matrix_uint4x3_sized.hpp"
    "vendor/glm/glm/ext/matrix_uint4x4.hpp"
    "vendor/glm/glm/ext/matrix_uint4x4_sized.hpp"
    "vendor/glm/glm/ext/quaternion_common.hpp"
    "vendor/glm/glm/ext/quaternion_common.inl"
    "vendor/glm/glm/ext/quaternion_common_simd.inl"
    "vendor/glm/glm/ext/quaternion_double.hpp"
    "vendor/glm/glm/ext/quaternion_double_precision.hpp"
    "vendor/glm/glm/ext/quaternion_exponential.hpp"
    "vendor/glm/glm/ext/quaternion_exponential.inl"
    "vendor/glm/glm/ext/quaternion_float.hpp"
    "vendor/glm/glm/ext/quaternion_float_precision.hpp"
    "vendor/glm/glm/ext/quaternion_geometric.hpp"
    "vendor/glm/glm/ext/quaternion_geometric.inl"
    "vendor/glm/glm/ext/quaternion_relational.hpp"
    "vendor/glm/glm/ext/quaternion_relational.inl"
    "vendor/glm/glm/ext/quaternion_transform.hpp"
    "vendor/glm/glm/ext/quaternion_transform.inl"
    "vendor/glm/glm/ext/quaternion_trigonometric.hpp"
    "vendor/glm/glm/ext/quaternion_trigonometric.inl"
    "vendor/glm/glm/ext/scalar_common.hpp"
    "vendor/glm/glm/ext/scalar_common.inl"
    "vendor/glm/glm/ext/scalar_constants.hpp"
    "vendor/glm/glm/ext/scalar_constants.inl"
    "vendor/glm/glm/ext/scalar_int_sized.hpp"
    "vendor/glm/glm/ext/scalar_integer.hpp"
    "vendor/glm/glm/ext/scalar_integer.inl"
    "vendor/glm/glm/ext/scalar_packing.hpp"
    "vendor/glm/glm/ext/scalar_packing.inl"
    "vendor/glm/glm/ext/scalar_reciprocal.hpp"
    "vendor/glm/glm/ext/scalar_reciprocal.inl"
    "vendor/glm/glm/ext/scalar_relational.hpp"
    "vendor/glm/glm/ext/scalar_relational.inl"
    "vendor/glm/glm/ext/scalar_uint_sized.hpp"
    "vendor/glm/glm/ext/scalar_ulp.hpp"
    "vendor/glm/glm/ext/scalar_ulp.inl"
    "vendor/glm/glm/ext/vector_bool1.hpp"
    "vendor/glm/glm/ext/vector_bool1_precision.hpp"
    "vendor/glm/glm/ext/vector_bool2.hpp"
    "vendor/glm/glm/ext/vector_bool2_precision.hpp"
    "vendor/glm/glm/ext/vector_bool3.hpp"
    "vendor/glm/glm/ext/vector_bool3_precision.hpp"
    "vendor/glm/glm/ext/vector_bool4.hpp"
    "vendor/glm/glm/ext/vector_bool4_precision.hpp"
    "vendor/glm/glm/ext/vector_common.hpp"
    "vendor/glm/glm/ext/vector_common.inl"
    "vendor/glm/glm/ext/vector_double1.hpp"
    "vendor/glm/glm/ext/vector_double1_precision.hpp"
    "vendor/glm/glm/ext/vector_double2.hpp"
    "vendor/glm/glm/ext/vector_double2_precision.hpp"
    "vendor/glm/glm/ext/vector_double3.hpp"
    "vendor/glm/glm/ext/vector_double3_precision.hpp"
    "vendor/glm/glm/ext/vector_double4.hpp"
    "vendor/glm/glm/ext/vector_double4_precision.hpp"
    "vendor/glm/glm/ext/vector_float1.hpp"
    "vendor/glm/glm/ext/vector_float1_precision.hpp"
    "vendor/glm/glm/ext/vector_float2.hpp"
    "vendor/glm/glm/ext/vector_float2_precision.hpp"
    "vendor/glm/glm/ext/vector_float3.hpp"
    "vendor/glm/glm/ext/vector_float3_precision.hpp"
    "vendor/glm/glm/ext/vector_float4.hpp"
    "vendor/glm/glm/ext/vector_float4_precision.hpp"
    "vendor/glm/glm/ext/vector_int1.hpp"
    "vendor/glm/glm/ext/vector_int1_sized.hpp"
    "vendor/glm/glm/ext/vector_int2.hpp"
    "vendor/glm/glm/ext/vector_int2_sized.hpp"
    "vendor/glm/glm/ext/vector_int3.hpp"
    "vendor/glm/glm/ext/vector_int3_sized.hpp"
    "vendor/glm/glm/ext/vector_int4.hpp"
    "vendor/glm/glm/ext/vector_int4_sized.hpp"
    "vendor/glm/glm/ext/vector_integer.hpp"
    "vendor/glm/glm/ext/vector_integer.inl"
    "vendor/glm/glm/ext/vector_packing.hpp"
    "vendor/glm/glm/ext/vector_packing.inl"
    "vendor/glm/glm/ext/vector_reciprocal.hpp"
    "vendor/glm/glm/ext/vector_reciprocal.inl"
    "vendor/glm/glm/ext/vector_relational.hpp"
    "vendor/glm/glm/ext/vector_relational.inl"
    "vendor/glm/glm/ext/vector_uint1.hpp"
    "vendor/glm/glm/ext/vector_uint1_sized.hpp"
    "vendor/glm/glm/ext/vector_uint2.hpp"
    "vendor/glm/glm/ext/vector_uint2_sized.hpp"
    "vendor/glm/glm/ext/vector_uint3.hpp"
    "vendor/glm/glm/ext/vector_uint3_sized.hpp"
    "vendor/glm/glm/ext/vector_uint4.hpp"
    "vendor/glm/glm/ext/vector_uint4_sized.hpp"
    "vendor/glm/glm/ext/vector_ulp.hpp"
    "vendor/glm/glm/ext/vector_ulp.inl"
)
source_group("vendor\\glm\\glm\\ext" FILES ${vendor__glm__glm__ext})

set(vendor__glm__glm__gtc
    "vendor/glm/glm/gtc/bitfield.hpp"
    "vendor/glm/glm/gtc/bitfield.inl"
    "vendor/glm/glm/gtc/color_space.hpp"
    "vendor/glm/glm/gtc/color_space.inl"
    "vendor/glm/glm/gtc/constants.hpp"
    "vendor/glm/glm/gtc/constants.inl"
    "vendor/glm/glm/gtc/epsilon.hpp"
    "vendor/glm/glm/gtc/epsilon.inl"
    "vendor/glm/glm/gtc/integer.hpp"
    "vendor/glm/glm/gtc/integer.inl"
    "vendor/glm/glm/gtc/matrix_access.hpp"
    "vendor/glm/glm/gtc/matrix_access.inl"
    "vendor/glm/glm/gtc/matrix_integer.hpp"
    "vendor/glm/glm/gtc/matrix_inverse.hpp"
    "vendor/glm/glm/gtc/matrix_inverse.inl"
    "vendor/glm/glm/gtc/matrix_transform.hpp"
    "vendor/glm/glm/gtc/matrix_transform.inl"
    "vendor/glm/glm/gtc/noise.hpp"
    "vendor/glm/glm/gtc/noise.inl"
    "vendor/glm/glm/gtc/packing.hpp"
    "vendor/glm/glm/gtc/packing.inl"
    "vendor/glm/glm/gtc/quaternion.hpp"
    "vendor/glm/glm/gtc/quaternion.inl"
    "vendor/glm/glm/gtc/quaternion_simd.inl"
    "vendor/glm/glm/gtc/random.hpp"
    "vendor/glm/glm/gtc/random.inl"
    "vendor/glm/glm/gtc/reciprocal.hpp"
    "vendor/glm/glm/gtc/round.hpp"
    "vendor/glm/glm/gtc/round.inl"
    "vendor/glm/glm/gtc/type_aligned.hpp"
    "vendor/glm/glm/gtc/type_precision.hpp"
    "vendor/glm/glm/gtc/type_precision.inl"
    "vendor/glm/glm/gtc/type_ptr.hpp"
    "vendor/glm/glm/gtc/type_ptr.inl"
    "vendor/glm/glm/gtc/ulp.hpp"
    "vendor/glm/glm/gtc/ulp.inl"
    "vendor/glm/glm/gtc/vec1.hpp"
)
source_group("vendor\\glm\\glm\\gtc" FILES ${vendor__glm__glm__gtc})

set(vendor__glm__glm__gtx
    "vendor/glm/glm/gtx/associated_min_max.hpp"
    "vendor/glm/glm/gtx/associated_min_max.inl"
    "vendor/glm/glm/gtx/bit.hpp"
    "vendor/glm/glm/gtx/bit.inl"
    "vendor/glm/glm/gtx/closest_point.hpp"
    "vendor/glm/glm/gtx/closest_point.inl"
    "vendor/glm/glm/gtx/color_encoding.hpp"
    "vendor/glm/glm/gtx/color_encoding.inl"
    "vendor/glm/glm/gtx/color_space.hpp"
    "vendor/glm/glm/gtx/color_space.inl"
    "vendor/glm/glm/gtx/color_space_YCoCg.hpp"
    "vendor/glm/glm/gtx/color_space_YCoCg.inl"
    "vendor/glm/glm/gtx/common.hpp"
    "vendor/glm/glm/gtx/common.inl"
    "vendor/glm/glm/gtx/compatibility.hpp"
    "vendor/glm/glm/gtx/compatibility.inl"
    "vendor/glm/glm/gtx/component_wise.hpp"
    "vendor/glm/glm/gtx/component_wise.inl"
    "vendor/glm/glm/gtx/dual_quaternion.hpp"
    "vendor/glm/glm/gtx/dual_quaternion.inl"
    "vendor/glm/glm/gtx/easing.hpp"
    "vendor/glm/glm/gtx/easing.inl"
    "vendor/glm/glm/gtx/euler_angles.hpp"
    "vendor/glm/glm/gtx/euler_angles.inl"
    "vendor/glm/glm/gtx/extend.hpp"
    "vendor/glm/glm/gtx/extend.inl"
    "vendor/glm/glm/gtx/extended_min_max.hpp"
    "vendor/glm/glm/gtx/extended_min_max.inl"
    "vendor/glm/glm/gtx/exterior_product.hpp"
    "vendor/glm/glm/gtx/exterior_product.inl"
    "vendor/glm/glm/gtx/fast_exponential.hpp"
    "vendor/glm/glm/gtx/fast_exponential.inl"
    "vendor/glm/glm/gtx/fast_square_root.hpp"
    "vendor/glm/glm/gtx/fast_square_root.inl"
    "vendor/glm/glm/gtx/fast_trigonometry.hpp"
    "vendor/glm/glm/gtx/fast_trigonometry.inl"
    "vendor/glm/glm/gtx/float_notmalize.inl"
    "vendor/glm/glm/gtx/functions.hpp"
    "vendor/glm/glm/gtx/functions.inl"
    "vendor/glm/glm/gtx/gradient_paint.hpp"
    "vendor/glm/glm/gtx/gradient_paint.inl"
    "vendor/glm/glm/gtx/handed_coordinate_space.hpp"
    "vendor/glm/glm/gtx/handed_coordinate_space.inl"
    "vendor/glm/glm/gtx/hash.hpp"
    "vendor/glm/glm/gtx/hash.inl"
    "vendor/glm/glm/gtx/integer.hpp"
    "vendor/glm/glm/gtx/integer.inl"
    "vendor/glm/glm/gtx/intersect.hpp"
    "vendor/glm/glm/gtx/intersect.inl"
    "vendor/glm/glm/gtx/io.hpp"
    "vendor/glm/glm/gtx/io.inl"
    "vendor/glm/glm/gtx/log_base.hpp"
    "vendor/glm/glm/gtx/log_base.inl"
    "vendor/glm/glm/gtx/matrix_cross_product.hpp"
    "vendor/glm/glm/gtx/matrix_cross_product.inl"
    "vendor/glm/glm/gtx/matrix_decompose.hpp"
    "vendor/glm/glm/gtx/matrix_decompose.inl"
    "vendor/glm/glm/gtx/matrix_factorisation.hpp"
    "vendor/glm/glm/gtx/matrix_factorisation.inl"
    "vendor/glm/glm/gtx/matrix_interpolation.hpp"
    "vendor/glm/glm/gtx/matrix_interpolation.inl"
    "vendor/glm/glm/gtx/matrix_major_storage.hpp"
    "vendor/glm/glm/gtx/matrix_major_storage.inl"
    "vendor/glm/glm/gtx/matrix_operation.hpp"
    "vendor/glm/glm/gtx/matrix_operation.inl"
    "vendor/glm/glm/gtx/matrix_query.hpp"
    "vendor/glm/glm/gtx/matrix_query.inl"
    "vendor/glm/glm/gtx/matrix_transform_2d.hpp"
    "vendor/glm/glm/gtx/matrix_transform_2d.inl"
    "vendor/glm/glm/gtx/mixed_product.hpp"
    "vendor/glm/glm/gtx/mixed_product.inl"
    "vendor/glm/glm/gtx/norm.hpp"
    "vendor/glm/glm/gtx/norm.inl"
    "vendor/glm/glm/gtx/normal.hpp"
    "vendor/glm/glm/gtx/normal.inl"
    "vendor/glm/glm/gtx/normalize_dot.hpp"
    "vendor/glm/glm/gtx/normalize_dot.inl"
    "vendor/glm/glm/gtx/number_precision.hpp"
    "vendor/glm/glm/gtx/number_precision.inl"
    "vendor/glm/glm/gtx/optimum_pow.hpp"
    "vendor/glm/glm/gtx/optimum_pow.inl"
    "vendor/glm/glm/gtx/orthonormalize.hpp"
    "vendor/glm/glm/gtx/orthonormalize.inl"
    "vendor/glm/glm/gtx/pca.hpp"
    "vendor/glm/glm/gtx/pca.inl"
    "vendor/glm/glm/gtx/perpendicular.hpp"
    "vendor/glm/glm/gtx/perpendicular.inl"
    "vendor/glm/glm/gtx/polar_coordinates.hpp"
    "vendor/glm/glm/gtx/polar_coordinates.inl"
    "vendor/glm/glm/gtx/projection.hpp"
    "vendor/glm/glm/gtx/projection.inl"
    "vendor/glm/glm/gtx/quaternion.hpp"
    "vendor/glm/glm/gtx/quaternion.inl"
    "vendor/glm/glm/gtx/range.hpp"
    "vendor/glm/glm/gtx/raw_data.hpp"
    "vendor/glm/glm/gtx/raw_data.inl"
    "vendor/glm/glm/gtx/rotate_normalized_axis.hpp"
    "vendor/glm/glm/gtx/rotate_normalized_axis.inl"
    "vendor/glm/glm/gtx/rotate_vector.hpp"
    "vendor/glm/glm/gtx/rotate_vector.inl"
    "vendor/glm/glm/gtx/scalar_multiplication.hpp"
    "vendor/glm/glm/gtx/scalar_relational.hpp"
    "vendor/glm/glm/gtx/scalar_relational.inl"
    "vendor/glm/glm/gtx/spline.hpp"
    "vendor/glm/glm/gtx/spline.inl"
    "vendor/glm/glm/gtx/std_based_type.hpp"
    "vendor/glm/glm/gtx/std_based_type.inl"
    "vendor/glm/glm/gtx/string_cast.hpp"
    "vendor/glm/glm/gtx/string_cast.inl"
    "vendor/glm/glm/gtx/texture.hpp"
    "vendor/glm/glm/gtx/texture.inl"
    "vendor/glm/glm/gtx/transform.hpp"
    "vendor/glm/glm/gtx/transform.inl"
    "vendor/glm/glm/gtx/transform2.hpp"
    "vendor/glm/glm/gtx/transform2.inl"
    "vendor/glm/glm/gtx/type_aligned.hpp"
    "vendor/glm/glm/gtx/type_aligned.inl"
    "vendor/glm/glm/gtx/type_trait.hpp"
    "vendor/glm/glm/gtx/type_trait.inl"
    "vendor/glm/glm/gtx/vec_swizzle.hpp"
    "vendor/glm/glm/gtx/vector_angle.hpp"
    "vendor/glm/glm/gtx/vector_angle.inl"
    "vendor/glm/glm/gtx/vector_query.hpp"
    "vendor/glm/glm/gtx/vector_query.inl"
    "vendor/glm/glm/gtx/wrap.hpp"
    "vendor/glm/glm/gtx/wrap.inl"
)
source_group("vendor\\glm\\glm\\gtx" FILES ${vendor__glm__glm__gtx})

set(vendor__stb_image
    "vendor/stb_image/stb_image.cpp"
    "vendor/stb_image/stb_image.h"
)
source_group("vendor\\stb_image" FILES ${vendor__stb_image})

set(ALL_FILES
    ${src}
    ${src__FoxEngine__Core}
    ${src__FoxEngine__Debug}
    ${src__FoxEngine__Event}
    ${src__FoxEngine__ImGui}
    ${src__FoxEngine__Platform__OpenGL}
    ${src__FoxEngine__Platform__Windows}
    ${src__FoxEngine__Scene}
    ${src__FoxEngine__Renderer}
    ${vendor__glm__glm}
    ${vendor__glm__glm__detail}
    ${vendor__glm__glm__ext}
    ${vendor__glm__glm__gtc}
    ${vendor__glm__glm__gtx}
    ${vendor__stb_image}
        src/FoxEngine/Scene/ScriptableEntity.cpp src/FoxEngine/Scene/ScriptableEntity.h)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})

target_precompile_headers(${PROJECT_NAME} PRIVATE "src/fepch.h")

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE FoxEngine)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    TARGET_NAME_DEBUG        "FoxEngine"
    TARGET_NAME_DISTRIBUTION "FoxEngine"
    TARGET_NAME_RELEASE      "FoxEngine"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_DEBUG        "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Debug-windows-x86_64/FoxEngine/"
    OUTPUT_DIRECTORY_DISTRIBUTION "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Distribution-windows-x86_64/FoxEngine/"
    OUTPUT_DIRECTORY_RELEASE      "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Release-windows-x86_64/FoxEngine/"
)
################################################################################
# MSVC runtime library
################################################################################
get_property(MSVC_RUNTIME_LIBRARY_DEFAULT TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY)
string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
    $<$<CONFIG:Debug>:
        MultiThreadedDebug
    >
    $<$<CONFIG:Distribution>:
        MultiThreaded
    >
    $<$<CONFIG:Release>:
        MultiThreaded
    >
    $<$<NOT:$<OR:$<CONFIG:Debug>,$<CONFIG:Distribution>,$<CONFIG:Release>>>:${MSVC_RUNTIME_LIBRARY_DEFAULT}>
)
set_target_properties(${PROJECT_NAME} PROPERTIES MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_LIBRARY_STR})

################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src;"
    "${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog/include;"
    "${CMAKE_CURRENT_SOURCE_DIR}/vendor/GLFW/include;"
    "${CMAKE_CURRENT_SOURCE_DIR}/vendor/GLAD/include;"
    "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui;"
    "${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm;"
    "${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb_image;"
    "${CMAKE_CURRENT_SOURCE_DIR}/vendor/entt"
)

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "$<$<CONFIG:Debug>:"
        "FOX_DEBUG"
    ">"
    "$<$<CONFIG:Distribution>:"
        "FOX_DISTRIBUTION"
    ">"
    "$<$<CONFIG:Release>:"
        "FOX_RELEASE"
    ">"
    "_CRT_SECURE_NO_WARNINGS;"
    "FOX_PLATFORM_WINDOWS;"
    "FOX_BUILD_DLL;"
    "GLFW_INCLUDE_NONE;"
    "UNICODE;"
    "_UNICODE"
)

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            /Od;
            /ZI;
            /MDd
        >
        $<$<CONFIG:Distribution>:
            /Gm-;
            /Ox;
            /Oi;
            /GF;
            /Gy;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            /MD
        >
        $<$<CONFIG:Release>:
            /Gm-;
            /Ox;
            /Oi;
            /GF;
            /Gy;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            /MD
        >
        /std:c++17;
        /W3;
        ${DEFAULT_CXX_EXCEPTION_HANDLING}
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Distribution>:
            /OPT:REF;
            /OPT:ICF
        >
        $<$<CONFIG:Release>:
            /OPT:REF;
            /OPT:ICF
        >
        /SUBSYSTEM:WINDOWS
    )
endif()

################################################################################
# Dependencies
################################################################################
add_dependencies(${PROJECT_NAME}
    GLFW
    GLAD
    ImGui
)

# Link with other targets.
target_link_libraries(${PROJECT_NAME} PUBLIC
    GLFW
    GLAD
    ImGui
)

set(ADDITIONAL_LIBRARY_DEPENDENCIES
    "opengl32"
)
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

