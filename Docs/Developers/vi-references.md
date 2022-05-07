# Tài liệu tham khảo Yuki Engine

## Cấu trúc mã nguồn

- Tổng quan

```
|----<MODULE_FOLDER> [D]
    |---- Include   [D]
        |----<SUB_MODULE_INCLUDE_FOLDER_1>  [D]
        |----<SUB_MODULE_INCLUDE_FOLDER_2>  [D]
        |----...
    |----- Srcs     [D] 
```

- Core Module

```
|---- YukiCore [D]
    |---- Include [D]
        |---- YukiComp [D] - Các thành phần cấu thành
        |---- YukiCore [D] - Các yếu tố cốt lõi của engine
        |---- YukiDebug [D] - Lỗi, logging,...
        |---- YukiEntity [D] - Thực thể mặc định
        |---- YukiUtils [D] - Công cụ hữu ích
    |---- Srcs [D]
```

- Thư viện phụ thuộc

```
|---- YukiDeps [D]
    |---- Debug [D]
        |---- Binaries [D]
        |---- Libraries [D]
    |---- Includes [D]
    |---- Release [D]
        |---- Binaries [D]
        |---- Libraries [D}
```

- Shader

```
|---- YukiShader [D]
    |---- <SHADER_NAME>.vert [F] - Vertex shader
    |---- <SHADER_NAME>.geom [F] - Geometry shader
    |---- <SHADER_NAME>.frag [F] - Fragment shader
```

## Phong cách code

1. Thư mục, file

- Các file header phải có phần mở rộng `.hpp`, các file mã nguồn cần có phần mở rộng `.cpp`
- Tên thư mục, file cần được viết bằng CamelCase với chữ cái đầu tiên viết hoa
- Tên thư mục module, tên file liên quan đến engine cần có tiền tố `Yuki`, ngoại trừ các file liên quan đến
  các thực
  thể (Entities)
  ```
  [X] YukiLogger.hxx
  [X] InputControl.hpp
  [V] YukiLogger.hpp
  [V] Entity.hpp
  [V] CameraControlEntity.hpp
  [V] YukiApplication.cpp
  ```
- Các header riêng (private headers) cần có tiền tố `P` và đi sau là tên của interface cần triển khai.
  ```
  [V] PYukiApplication.hpp
  ```
- File header cần có phần mở đầu file bao gồm các thông tin: `Author`, `Country`, `License`...
  ```
  /**
   * ===========================================
   * Author:          vn-vna (Anh Vu)
   * Country:         Vietnam
   * License:         MIT
   * ===========================================
   */
  ```
- Code phải được format bằng clang-format với quy tắc được định trong file [`.clang-format`](../../.clang-format)

2. Namespace

- Tên namespace phải được viết bằng CamelCase, chữ cái đầu tiên viết hoa
- Cấu trúc:

```
|---- ::Yuki
    |---- ::Core
    |---- ::Comp
    |---- ::Debug
    |---- ::Utils
    |---- ::MoreModule
    |---- ::OneMoreModule
    |---- ...
```

3. Class

- Tên class phải được viết bằng CamelCase với chữ cái đầu tiên viết hoa
- Immutable class
    - Immutable class phải được tổ chức theo cấu trúc
  ```
  Interface -> PrivateClass -> Definition
  ```
    - Nếu các class kế thừa nhau phải được kế thừa bằng `virtual inheritance`
  ```
  Interface1 -> Interface1Class
    \ <virtual>  / <virtual>
     \          /
      Interface2 -> Interface2Class
  ```

4. Biến, trường
  
5. Hàm, phương thức
6. Typedef