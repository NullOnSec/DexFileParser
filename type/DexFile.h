#ifndef DEX_FILE_H
#define DEX_FILE_H

#include <cstdint>
#include <iostream>
#include <string>
#include "../util/Printer.h"
#include "Leb128.h"


using namespace std;

typedef uint8_t   u1;
typedef uint16_t  u2;
typedef uint32_t  u4;
typedef uint64_t  u8;
typedef int8_t    s1;
typedef int16_t   s2;
typedef int32_t   s4;
typedef int64_t   s8;

//typedef u1* uleb128;
//typedef u1* uleb128p1;

struct uleb128
{
    uleb128(): value(0), data(nullptr), length(0) {}
    ~uleb128()
    {
       if (this->data != nullptr)
       {
           delete[] this->data;
           this->data = nullptr;
       }
    }

    u4 value;
    u1* data;
    u4 length;
};

struct uleb128p1
{
    uleb128p1() : value(0), data(nullptr), length(0) {}
    ~uleb128p1()
    {
        if (this->data != nullptr)
        {
            delete[] this->data;
            this->data = nullptr;
        }
    }

    u4 value;
    u1* data;
    u4 length;
};

inline void parse_uleb128(/* u1[5] */u1* leb128_buffer, uleb128 *p)
{
    const u1* p1 = leb128_buffer;
    const auto data = &p1;

    const auto size = Leb128::decode_unsigned_leb128(data);
    const auto length = Leb128::unsigned_leb128_size(size);

    p->value = size;
    p->data = leb128_buffer;
    p->length = length;
}

// �ֽ����ǳ�����
enum
{
    ENDIAN_CONSTANT         = 0x12345678,
    REVERSE_ENDIAN_CONSTANT = 0x78563412,
};

enum
{
    TYPE_HEADER_ITEM                = 0x0000, // header_item	            size: 0x70
    TYPE_STRING_ID_ITEM             = 0x0001, // string_id_item	            size: 0x04
    TYPE_TYPE_ID_ITEM               = 0x0002, // type_id_item	            size: 0x04
    TYPE_PROTO_ID_ITEM              = 0x0003, // proto_id_item	            size: 0x0c
    TYPE_FIELD_ID_ITEM              = 0x0004, // field_id_item	            size: 0x08
    TYPE_METHOD_ID_ITEM             = 0x0005, // method_id_item	            size: 0x08
    TYPE_CLASS_DEF_ITEM             = 0x0006, // class_def_item	            size: 0x20
    TYPE_CALL_SITE_ID_ITEM          = 0x0007, // call_site_id_item	        size: 0x04
    TYPE_METHOD_HANDLE_ITEM         = 0x0008, // method_handle_item	        size: 0x08
    TYPE_MAP_LIST                   = 0x1000, // map_list	                size: 4 + (item.size * 12)
    TYPE_TYPE_LIST                  = 0x1001, // type_list	                size: 4 + (item.size * 2)
    TYPE_ANNOTATION_SET_REF_LIST    = 0x1002, // annotation_set_ref_list    size: 4 + (item.size * 4)
    TYPE_ANNOTATION_SET_ITEM        = 0x1003, // annotation_set_item	    size: 4 + (item.size * 4)
    TYPE_CLASS_DATA_ITEM            = 0x2000, // class_data_item	        size: ��ʽ���������
    TYPE_CODE_ITEM                  = 0x2001, // code_item	                size: ��ʽ���������
    TYPE_STRING_DATA_ITEM           = 0x2002, // string_data_item	        size: ��ʽ���������
    TYPE_DEBUG_INFO_ITEM            = 0x2003, // debug_info_item	        size: ��ʽ���������
    TYPE_ANNOTATION_ITEM            = 0x2004, // annotation_item	        size: ��ʽ���������
    TYPE_ENCODED_ARRAY_ITEM         = 0x2005, // encoded_array_item	        size: ��ʽ���������
    TYPE_ANNOTATIONS_DIRECTORY_ITEM = 0x2006, // annotations_directory_item size: ��ʽ���������
};

inline const char* type_string(const u2 type)
{
    switch (type)
    {
    case TYPE_HEADER_ITEM:return "header_item";
    case TYPE_STRING_ID_ITEM:return "string_id_item";
    case TYPE_TYPE_ID_ITEM:return "type_id_item";
    case TYPE_PROTO_ID_ITEM:return "proto_id_item";
    case TYPE_FIELD_ID_ITEM:return "field_id_item";
    case TYPE_METHOD_ID_ITEM:return "method_id_item";
    case TYPE_CLASS_DEF_ITEM:return "class_def_item";
    case TYPE_CALL_SITE_ID_ITEM:return "call_site_id_item";
    case TYPE_METHOD_HANDLE_ITEM:return "method_handle_item";
    case TYPE_MAP_LIST:return "map_list";
    case TYPE_TYPE_LIST:return "type_list";
    case TYPE_ANNOTATION_SET_REF_LIST:return "annotation_set_ref_list";
    case TYPE_ANNOTATION_SET_ITEM:return "annotation_set_item";
    case TYPE_CLASS_DATA_ITEM:return "class_data_item";
    case TYPE_CODE_ITEM:return "code_item";
    case TYPE_STRING_DATA_ITEM:return "string_data_item";
    case TYPE_DEBUG_INFO_ITEM:return "debug_info_item";
    case TYPE_ANNOTATION_ITEM:return "annotation_item";
    case TYPE_ENCODED_ARRAY_ITEM:return "encoded_array_item";
    case TYPE_ANNOTATIONS_DIRECTORY_ITEM:return "annotations_directory_item";
    default:return"KNOWN";
    }
}

enum {
    ACC_PUBLIC      = 0x00000001,       // class, field, method, ic
    ACC_PRIVATE     = 0x00000002,       // field, method, ic
    ACC_PROTECTED   = 0x00000004,       // field, method, ic
    ACC_STATIC      = 0x00000008,       // field, method, ic
    ACC_FINAL       = 0x00000010,       // class, field, method, ic
    ACC_SYNCHRONIZED= 0x00000020,       // method (only allowed on natives)
    ACC_SUPER       = 0x00000020,       // class (not used in Dalvik)
    ACC_VOLATILE    = 0x00000040,       // field
    ACC_BRIDGE      = 0x00000040,       // method (1.5)
    ACC_TRANSIENT   = 0x00000080,       // field
    ACC_VARARGS     = 0x00000080,       // method (1.5)
    ACC_NATIVE      = 0x00000100,       // method
    ACC_INTERFACE   = 0x00000200,       // class, ic
    ACC_ABSTRACT    = 0x00000400,       // class, method, ic
    ACC_STRICT      = 0x00000800,       // method
    ACC_SYNTHETIC   = 0x00001000,       // field, method, ic
    ACC_ANNOTATION  = 0x00002000,       // class, ic (1.5)
    ACC_ENUM        = 0x00004000,       // class, field, ic (1.5)
    ACC_CONSTRUCTOR = 0x00010000,       // method (Dalvik only)
    ACC_DECLARED_SYNCHRONIZED = 0x00020000, // method (Dalvik only)
    ACC_CLASS_MASK =
    (ACC_PUBLIC | ACC_FINAL | ACC_INTERFACE | ACC_ABSTRACT
        | ACC_SYNTHETIC | ACC_ANNOTATION | ACC_ENUM),
    ACC_INNER_CLASS_MASK =
    (ACC_CLASS_MASK | ACC_PRIVATE | ACC_PROTECTED | ACC_STATIC),
    ACC_FIELD_MASK =
    (ACC_PUBLIC | ACC_PRIVATE | ACC_PROTECTED | ACC_STATIC | ACC_FINAL
        | ACC_VOLATILE | ACC_TRANSIENT | ACC_SYNTHETIC | ACC_ENUM),
    ACC_METHOD_MASK =
    (ACC_PUBLIC | ACC_PRIVATE | ACC_PROTECTED | ACC_STATIC | ACC_FINAL
        | ACC_SYNCHRONIZED | ACC_BRIDGE | ACC_VARARGS | ACC_NATIVE
        | ACC_ABSTRACT | ACC_STRICT | ACC_SYNTHETIC | ACC_CONSTRUCTOR
        | ACC_DECLARED_SYNCHRONIZED),
};

inline void print_access_flags_description(u4 flags)
{
    string desc;

    if ((flags & ACC_PUBLIC) != 0)
        desc += "public ";

    if ((flags & ACC_PRIVATE) != 0)
        desc += "private ";

    if ((flags & ACC_PROTECTED) != 0)
        desc += "protected ";

    if ((flags & ACC_STATIC) != 0)
        desc += "static ";

    if ((flags & ACC_FINAL) != 0)
        desc += "final ";

    if ((flags & ACC_SYNCHRONIZED) != 0)
        desc += "synchronized ";

    if ((flags & ACC_SUPER) != 0)
        desc += "super ";

    if ((flags & ACC_VOLATILE) != 0)
        desc += "volatile ";

    if ((flags & ACC_BRIDGE) != 0)
        desc += "bridge ";

    if ((flags & ACC_TRANSIENT) != 0)
        desc += "transient ";

    if ((flags & ACC_VARARGS) != 0)
        desc += "varargs ";

    if ((flags & ACC_NATIVE) != 0)
        desc += "native ";

    if ((flags & ACC_INTERFACE) != 0)
        desc += "interface ";

    if ((flags & ACC_ABSTRACT) != 0)
        desc += "abstract ";

    if ((flags & ACC_STRICT) != 0)
        desc += "strict ";

    if ((flags & ACC_SYNTHETIC) != 0)
        desc += "synthetic ";

    if ((flags & ACC_ANNOTATION) != 0)
        desc += "annotation ";

    if ((flags & ACC_ENUM) != 0)
        desc += "enum ";

    if ((flags & ACC_CONSTRUCTOR) != 0)
        desc += "constructor ";

    if ((flags & ACC_DECLARED_SYNCHRONIZED) != 0)
        desc += "declared synchronized ";

    printf("%s", desc.c_str());
}

struct header_item
{
    header_item() :magic{ 0 }, checksum(0), signature{ 0 }, file_size(0),
        header_size(0), endian_tag(0), link_size(0), link_off(0), map_off(0),
        string_ids_size(0), string_ids_off(0), type_ids_size(0),type_ids_off(0),
        proto_ids_size(0), proto_ids_off(0), field_ids_size(0), field_ids_off(0),
        method_ids_size(0), method_ids_off(0), class_defs_size(0), class_defs_off(0),
        data_size(0), data_off(0) {}
    /* ħ�� */
    u1 magic[8];
    /*
      �ļ�ʣ�����ݣ��� magic �ʹ��ֶ�֮�����������)�� adler32 У��ͣ�
      ���ڼ���ļ��������
     */
    u1 checksum;
    /*
      �ļ�ʣ�����ݣ��� magic��checksum �ʹ��ֶ�֮�����������)�� SHA-1 ǩ������ϣ)��
      ���ڶ��ļ�����Ψһ��ʶ��
     */
    u1 signature[20];
    /* �����ļ���������ͷ)�Ĵ�С�����ֽ�Ϊ��λ */
    u4 file_size;
    /*
      ��ͷ����������)�Ĵ�С�����ֽ�Ϊ��λ����һ����������һ���̶ȵ����/��ǰ�����ԣ�
      �������ø�ʽʧЧ��
     */
    u4 header_size;
    /* �ֽ����� */
    u4 endian_tag;
    /* �������εĴ�С��������ļ�δ���о�̬���ӣ����ֵΪ 0 */
    u4 link_size;
    /*
      ���ļ���ͷ���������ε�ƫ��������� link_size == 0�����ֵΪ 0��
      ��ƫ���������Ϊ����ֵ)Ӧ���ǵ� link_data ���ε�ƫ������
     */
    u4 link_off;
    /* ���ļ���ͷ��ӳ�����ƫ��������ƫ����������Ϊ����)Ӧ���ǵ� data ���ε�ƫ���� */
    u4 map_off;
    /* �ַ�����ʶ���б��е��ַ������� */
    u4 string_ids_size;
    /*
      ���ļ���ͷ���ַ�����ʶ���б��ƫ��������� string_ids_size == 0���������)��
      ���ֵΪ 0����ƫ���������Ϊ����ֵ)Ӧ���ǵ� string_ids ���ο�ͷ��ƫ������
     */
    u4 string_ids_off;
    /* ���ͱ�ʶ���б��е�Ԫ�����������Ϊ 65535 */
    u4 type_ids_size;
    /*
      ���ļ���ͷ�����ͱ�ʶ���б��ƫ��������� type_ids_size == 0���������)��
      ���ֵΪ 0����ƫ���������Ϊ����ֵ)Ӧ���ǵ� type_ids ���ο�ͷ��ƫ������
     */
    u4 type_ids_off;
    /* ԭ�ͱ�ʶ���б��е�Ԫ�����������Ϊ 65535 */
    u4 proto_ids_size;
    /*
      ���ļ���ͷ��ԭ�ͱ�ʶ���б��ƫ��������� proto_ids_size == 0���������)��
      ���ֵΪ 0����ƫ���������Ϊ����ֵ)Ӧ���ǵ� proto_ids ���ο�ͷ��ƫ������
     */
    u4 proto_ids_off;
    /* �ֶα�ʶ���б��е�Ԫ������ */
    u4 field_ids_size;
    /*
      ���ļ���ͷ���ֶα�ʶ���б��ƫ��������� field_ids_size == 0�����ֵΪ 0��
      ��ƫ���������Ϊ����ֵ)Ӧ���ǵ� field_ids ���ο�ͷ��ƫ������
     */
    u4 field_ids_off;
    /* ������ʶ���б��е�Ԫ������ */
    u4 method_ids_size;
    /*
      ���ļ���ͷ��������ʶ���б��ƫ��������� method_ids_size == 0�����ֵΪ 0��
      ��ƫ���������Ϊ����ֵ)Ӧ���ǵ� method_ids ���ο�ͷ��ƫ����
     */
    u4 method_ids_off;
    /* �ඨ���б��е�Ԫ������ */
    u4 class_defs_size;
    /*
      ���ļ���ͷ���ඨ���б��ƫ��������� class_defs_size == 0���������)��
      ���ֵΪ 0����ƫ���������Ϊ����ֵ)Ӧ���ǵ� class_defs ���ο�ͷ��ƫ������
     */
    u4 class_defs_off;
    /* data ���εĴ�С�����ֽ�Ϊ��λ)������ֵ������ sizeof(uint) ��ż���� */
    u4 data_size;
    /* ���ļ���ͷ�� data ���ο�ͷ��ƫ���� */
    u4 data_off;
};

struct map_item
{
    u2 type;   // ������͡�
    u2 unused; //��δʹ�á�
    u4 size;   // ��ָ��ƫ�������ҵ�����������
    u4 offset; // ���ļ���ͷ��������ƫ������
};

inline void print_map_item(map_item const* map_item)
{
    printf("\nmap_item:\n");
    printf("type: 0x%x\n", map_item->type);
    printf("type desc: %s\n", type_string(map_item->type));
    printf("size: %d\n", map_item->size);
    printf("offset: %u\n", map_item->offset);
}

struct map_list
{
    map_list(): size(0), list(nullptr) {} 

    explicit map_list(const u4 size)
    {
        this->size = size;
        this->list = new map_item[size];
    }

    ~map_list()
    {
        if (this->list != nullptr)
        {
            delete[] this->list;
            this->list = nullptr;
        }
    }

    u4 size;          // �б�Ĵ�С������Ŀ����ʾ����
    map_item* list;   // �б��Ԫ�ء�
};

struct string_id_item
{
    /*
      ���ļ���ͷ��������ַ������ݵ�ƫ��������ƫ����Ӧ���ǵ� data ������ĳ��λ�õ�
      ƫ������
     */
    u4 string_data_off;
};

struct string_data_item
{
    string_data_item():utf16_size(uleb128()), data(nullptr) {}
    ~string_data_item() = default;

    /*
      ���ַ����Ĵ�С���� UTF-16 ���뵥Ԫ�������ϵͳ��Ϊ���ַ������ȡ���Ϊ��λ��
      Ҳ����˵�����Ǹ��ַ����Ľ��볤�ȣ����볤�������� 0 �ֽڵ�λ�ã���
     */
    uleb128 utf16_size;
    /*
      һϵ�� MUTF-8 ���뵥Ԫ���ֳư�λ�ֽڣ������һ��ֵΪ 0 ���ֽڡ�
     */
    u1* data;
};

struct type_id_item
{
    /*
      �����������ַ����� string_ids �б��е����������ַ�������������Ķ����
      TypeDescriptor ���﷨��
     */
    u4 descriptor_idx;
};

struct proto_id_item
{
    /*
      ��ԭ�͵ļ��ʽ�������ַ����� string_ids �б��е����������ַ�������������Ķ���
      �� ShortyDescriptor ���﷨�����ұ��������ķ������ͺͲ������Ӧ��
     */
    u4 shorty_ids;
    /* ��ԭ�͵ķ������͵� type_ids �б��е����� */
    u4 return_type_idx;
    /*
      ���ļ���ͷ����ԭ�͵Ĳ��������б��ƫ�����������ԭ��û�в��������ֵΪ 0��
      ��ƫ���������Ϊ����ֵ��Ӧ��λ�� data �����У������е�����Ӧ����������
      ��"type_list"��ָ���ĸ�ʽ�����⣬���ö��б��е����� void �����κ����á�
     */
    u4 parameters_off;
};

struct field_id_item
{
    /*
      ���ֶεĶ������ type_ids �б��е���������������ǡ��ࡱ���ͣ��������ǡ����顱��
      ����Ԫ�����͡�
     */
    u2 class_idx;
    /* ���ֶε����͵� type_ids �б��е����� */
    u2 type_idx;
    /*
      ���ֶε����Ƶ� string_ids �б��е����������ַ�������������Ķ���� MemberName
      ���﷨��
     */
    u4 name_idx;
};

struct method_id_item
{
    /*
      �˷����Ķ������ type_ids �б��е���������������ǡ��ࡱ�����顱���ͣ���������
      ����Ԫ�����͡�
     */
    u2 class_idx;
    /* �˷�����ԭ�͵� proto_ids �б��е����� */
    u2 proto_idx;
    /*
      �˷������Ƶ� string_ids �б��е����������ַ�������������Ķ���� MemberName
      ���﷨��
     */
    u4 name_idx;
};

struct class_def_item
{
    /*
      ����� type_ids �б��е���������������ǡ��ࡱ���ͣ��������ǡ����顱�򡰻�Ԫ�����͡�
     */
    u4 class_idx;
    /*
      ��ķ��ʱ�ǣ�public��final �ȣ����й����飬����ġ�access_flags ���塱��
     */
    u4 access_flag;
    /*
     ����� type_ids �б��е��������������û�г��ࣨ�����Ǹ��࣬���� Object����
     ���ֵΪ����ֵ NO_INDEX�����������ڳ��࣬���������ǡ��ࡱ���ͣ���������
     �����顱�򡰻�Ԫ�����͡�
     */
    u4 superclass_idx;
    /*
      ���ļ���ͷ���ӿ��б��ƫ���������û�нӿڣ����ֵΪ 0����ƫ����Ӧ��λ�� data
      ���Σ������е�����Ӧ���������С�type_list��ָ���ĸ�ʽ�����б��ÿ��Ԫ�ض�������
      ���ࡱ���ͣ��������ǡ����顱�򡰻�Ԫ�����ͣ������Ҳ��ð����κ��ظ��
     */
    u4 interfaces_off;
    /*
     �ļ�����������ࣨ���ٴ󲿷֣���ԭʼ��Դ�����Ƶ� string_ids �б��е�������
     ���߸�ֵΪ����ֵ NO_INDEX���Ա�ʾȱ��������Ϣ���κ�ָ�������� debug_info_item
     �����Ը��Ǵ�Դ�ļ�����Ԥ������Ǵ������ֻ������һ��Դ�ļ���
     */
    u4 source_file_idx;
    /*
      ���ļ���ͷ�������ע�ͽṹ��ƫ�������������û��ע�ͣ����ֵΪ 0����ƫ����
      �����Ϊ����ֵ��Ӧ��λ�� data ���Σ������е�����Ӧ����������
      ��annotations_directory_item��ָ���ĸ�ʽ��ͬʱ�����������Ϊ������������á�
     */
    u4 annotations_off;
    /*
      ���ļ���ͷ������Ĺ��������ݵ�ƫ�������������û�������ݣ����ֵΪ 0���������
      �п��ܳ��֣����磬��������Ǳ�ǽӿڣ�����ƫ���������Ϊ����ֵ��Ӧ��λ�� data
      ���Σ������е�����Ӧ���������С�class_data_item��ָ���ĸ�ʽ��ͬʱ�����������
      Ϊ������������á�
     */
    u4 class_data_off;
    /*
      ���ļ���ͷ�� static �ֶεĳ�ʼֵ�б��ƫ���������û�и��б��������� static
      �ֶζ���ʹ�� 0 �� null ���г�ʼ���������ֵΪ 0����ƫ����Ӧ��λ�� data ���Σ�
      �����е�����Ӧ���������С�encoded_array_item��ָ���ĸ�ʽ��������Ĵ�С���ó���
      ������������ static �ֶε��������� static �ֶ�����Ӧ��Ԫ��Ӧ�������Ӧ��
      field_list ����������˳��ÿ������Ԫ�ص����;�����������Ӧ�ֶε�����������ƥ�䡣
      ����������е�Ԫ�ر� static �ֶ��е��٣���ʣ���ֶν�ʹ���ʵ����� 0 �� null
      ���г�ʼ����
     */
    u4 static_values_off;
};

struct call_site_id_item
{
    /*
      ���ļ���ͷ�����õ㶨���ƫ��������ƫ����Ӧλ�����������У������е�����Ӧ������
      ���С�call_site_item��ָ���ĸ�ʽ��
     */
    u4 call_site_off;
};

struct encoded_field
{
    encoded_field() : field_idx_diff(uleb128()), access_flags(uleb128()) {}

    /*
      ���ֶα�ʶ���������ƺ����������� field_ids �б��е�������
      �����ʾΪ���б���ǰһ��Ԫ�ص�����֮��Ĳ�ֵ���б��е�һ��Ԫ�ص�������ֱ�ӱ�ʾ������
     */
    uleb128 field_idx_diff;
    /*
      �ֶεķ��ʱ�ǣ�public��final �ȣ���
     */
    uleb128 access_flags;
};

struct encoded_method
{
    encoded_method() :method_idx_diff(uleb128()), access_flags(uleb128()),
        code_off(uleb128()) {}

    ~encoded_method() = default;
    /*
      �˷�����ʶ���������ƺ����������� method_ids �б��е�������
      �����ʾΪ���б���ǰһ��Ԫ�ص�����֮��Ĳ�ֵ���б��е�һ��Ԫ�ص�������ֱ�ӱ�ʾ������
     */
    uleb128 method_idx_diff;
    /*
      �����ķ��ʱ�ǣ�public��final �ȣ���
     */
    uleb128 access_flags;
    /*
      ���ļ���ͷ���˷�������ṹ��ƫ����������˷����� abstract �� native�����ֵΪ 0��
      ��ƫ����Ӧ���ǵ� data ������ĳ��λ�õ�ƫ���������ݸ�ʽ�����ĵġ�code_item��ָ����
     */
    uleb128 code_off;
};

struct class_data_item
{
    class_data_item():
        static_fields_size(uleb128()),
        instance_fields_size(uleb128()),
        direct_methods_size(uleb128()),
        virtual_methods_size(uleb128()),
        static_fields(nullptr),
        instance_fields(nullptr),
        direct_methods(nullptr),
        virtual_methods(nullptr) {}

    ~class_data_item()
    {
        this->static_fields = nullptr;
        this->instance_fields = nullptr;
        this->direct_methods = nullptr;
        this->virtual_methods = nullptr;
    }

    uleb128 static_fields_size;    // �����ж���ľ�̬�ֶε�������
    uleb128 instance_fields_size;  // �����ж����ʵ���ֶε�������
    uleb128 direct_methods_size;   // �����ж����ֱ�ӷ�����������
    uleb128 virtual_methods_size;  // �����ж�������ⷽ����������
    /*
      ����ľ�̬�ֶΣ���һϵ�б���Ԫ�ص���ʽ��ʾ����Щ�ֶα��밴 field_idx �������������
     */
    encoded_field* static_fields;
    /*
      �����ʵ���ֶΣ���һϵ�б���Ԫ�ص���ʽ��ʾ����Щ�ֶα��밴 field_idx �������������
     */
    encoded_field* instance_fields;
    /*
      �����ֱ�ӣ�static��private ���캯�����κ�һ������������һϵ�б���Ԫ�ص���ʽ
      ��ʾ����Щ�������밴 method_idx �������������
     */
    encoded_method* direct_methods;
    /*
      ��������⣨�� static��private ���캯������������һϵ�б���Ԫ�ص���ʽ��ʾ��
      ���б��ð����̳з��������Ǳ���������ʾ���า�ǡ���Щ�������밴 method_idx ��
      ��������������ⷽ���� method_idx �������κ�ֱ�ӷ�����ͬ��
     */
    encoded_method* virtual_methods;
};

struct type_item
{
    type_item() : type_idx(0) {}
    u2 type_idx;  // type_ids �б��е�������
};

struct type_list
{
    type_list(): size(0), list(type_item()) {}

    u4 size;          // �б�Ĵ�С������Ŀ����ʾ��
    type_item list;;  // �б��Ԫ�ء�
};

struct try_item
{
    try_item() :start_addr(0), insn_count(0), handler_off(0) {}
    /*
      ����Ŀ���ǵĴ�������ʼ��ַ���õ�ַ�ǵ���һ��������ָ�ͷ���ֵ� 16 λ����
      ��Ԫ�ļ�����
    */
    u4 start_addr;
    /*
      ����Ŀ�����ǵ� 16 λ���뵥Ԫ�������������ǣ������������һ�����뵥Ԫ�� 
      start_addr + insn_count - 1��
    */
    u2 insn_count;
    /*
      �ӹ����� encoded_catch_hander_list ��ͷ���ֵ�����Ŀ�� encoded_catch_handler 
      ��ƫ���������ֽ�Ϊ��λ������ƫ���������ǵ� encoded_catch_handler ��ͷ���ֵ�
      ƫ������
    */
    u2 handler_off;
};

struct encoded_type_addr_pair
{
    encoded_type_addr_pair() : type_ids(uleb128()), addr(uleb128()) {}

    uleb128 type_ids;  // Ҫ������쳣���͵� type_ids �б��е�������
    uleb128 addr;      // �������쳣���������ֽ����ַ��
};

struct encoded_catch_handler
{
    /*
      ���б��в������͵����������Ϊ�����������ֵ�ǲ������������ĸ���������������
      ��һ����ȫ�����񡱴���������磬size Ϊ 0 ��ʾ��������Ϊ��ȫ�����񡱣���û����
      ȷ���͵Ĳ���size Ϊ 2 ��ʾ��������ȷ���͵Ĳ��񣬵�û�С�ȫ���������͵Ĳ���
      size Ϊ -1 ��ʾ��һ����ȷ���͵Ĳ����һ����ȫ���������͵Ĳ���
    */
    uleb128 size;
    /*
      abs(size) ���������Ϣ����һ�ֲ������Ͷ�Ӧһ�������Ӧ�����ͽ��в��Ե�˳�����С�
    */
    encoded_type_addr_pair *handlers;
    /*
      ��ȫ�����񡱴��������ֽ����ַ��ֻ�е� size Ϊ������ʱ����Ԫ�زŻ���ڡ�
    */
    uleb128 catch_add_addr;
};

struct encode_catch_handler_list
{
    uleb128 size;  // �б�Ĵ�С������Ŀ����ʾ����
    /*
      ��������б��ʵ���б�ֱ�ӱ�ʾ������Ϊƫ���������������ӡ�
    */
    encoded_catch_handler* list;
};

struct code_item
{
    code_item() : registers_size(0), ins_size(0), outs_size(0), tries_size(0),
        debug_info_off(0), insns_size(0), insns(nullptr), padding(0),
        tries(nullptr), handlers(encode_catch_handler_list()) {}

    u2 registers_size; // �˴���ʹ�õļĴ���������
    u2 ins_size;       // �˴������÷����Ĵ��������������
    u2 outs_size;      // �˴�����з�����������Ĵ��������ռ��������
    /* 
      ��ʵ���� try_item �����������ֵΪ����ֵ������Щ�����ʾΪ tries ����
     ������λ�ڴ�ʵ���� insns �ĺ��棩�� 
    */
    u2 tries_size;
    /*
      ���ļ���ͷ���˴���ĵ�����Ϣ���к� + �ֲ�������Ϣ�����е�ƫ���������û����
      ����Ϣ�����ֵΪ 0����ƫ���������Ϊ����ֵ��Ӧ���ǵ� data ������ĳ��λ�õ�ƫ���������ݸ�ʽ�����ĵġ�debug_info_item��ָ����
    */
    u4 debug_info_off;
    u4 insns_size;   // ָ���б�Ĵ�С���� 16 λ���뵥ԪΪ��λ����
    /*
      �ֽ����ʵ�����顣insns �����д���ĸ�ʽ���渽�ĵ� Dalvik �ֽ���ָ������ע�⣬
      ���ܴ������Ϊ ushort �����飬������һЩ�ڲ��ṹ�����ڲ������ֽڶ��뷽ʽ��
      ���⣬�������ǡ��λ��ĳ���ֽ��򽻻��ļ��У��򽻻�������ֻ�ڵ��� ushort �Ͻ�
      �У��������ڽϴ���ڲ��ṹ�Ͻ��С�
    */
    u2* insns;
    /*
      ����ѡ��ʹ tries ʵ�����ֽڶ�������ֽ���䡣ֻ�� tries_size Ϊ����ֵ�� 
      insns_size ������ʱ����Ԫ�زŻ���ڡ�
    */
    u2 padding;
    /*
      ����ѡ�����ڱ�ʾ�ڴ����в����쳣��λ���Լ���ζ��쳣���д�������顣�������Ԫ
      ���ڷ�Χ�ڲ����ص�������ֵ��ַ���մӵ͵��ߵ�˳�����С�ֻ�� tries_size Ϊ����
      ֵʱ����Ԫ�زŻ���ڡ�
    */
    try_item* tries;
    /* 
      ����ѡ�����ڱ�ʾ�����������б�͹�����������ַ�����б���ֽڡ�ÿ�� try_item 
      �����е��˽ṹ�ķ���ƫ������ֻ�� tries_size Ϊ����ֵʱ����Ԫ�زŻ���ڡ�
    */
    encode_catch_handler_list handlers;
};

struct debug_info_item
{
    debug_info_item(): line_start(uleb128()), parameters_size(uleb128()),
        parameter_names(uleb128p1()){}

    /*
      ״̬���� line �Ĵ����ĳ�ʼֵ������ʾʵ�ʵ�λ����Ŀ��
     */
    uleb128 line_start;
    /*
      �ѱ���Ĳ������Ƶ�������ÿ������������Ӧ����һ�����ƣ���������ʵ�������� this
     ������У���
     */
    uleb128 parameters_size;
    /*
      �����������Ƶ��ַ���������NO_INDEX �ı���ֵ��ʾ�ù�������û�п��õ����ơ�
      ��������������ǩ�������ڷ�����������ǩ���С�
     */
    uleb128p1 parameter_names;
};

struct field_annotation
{
    field_annotation(): field_idx(0), annotations_off(0) {}

    /* �ֶΣ���ע�ͣ���ʶ�� field_ids �б��е����� */
    u4 field_idx;
    /*
      ���ļ���ͷ�����ֶε�ע���б��ƫ��������ƫ����Ӧ���ǵ� data ������ĳ��λ�õ�ƫ
      ���������ݸ�ʽ�����ĵġ�annotation_set_item��ָ����
     */
    u4 annotations_off;
};

struct method_annotation
{
    method_annotation(): method_idx(0), annotations_off(0) {}

    /* ��������ע�ͣ���ʶ�� method_ids �б��е����� */
    u4 method_idx;
    /*
      ���ļ���ͷ���÷���ע���б��ƫ��������ƫ����Ӧ���ǵ� data ������ĳ��λ�õ�ƫ������
      ���ݸ�ʽ�����ĵġ�annotation_set_item��ָ����
     */
    u4 annotations_off;
};

struct parameter_annotation
{
    parameter_annotation(): method_idx(0), annotations_off(0) {}

    /* �������������ע�ͣ���ʶ�� method_ids �б��е����� */
    u4 method_idx;
    /*
      ���ļ���ͷ���÷���������ע���б��ƫ��������ƫ����Ӧ���ǵ� data ������ĳ��λ�õ�
      ƫ���������ݸ�ʽ�����ĵġ�annotation_set_ref_list��ָ����
     */
    u4 annotations_off;
};

struct annotations_directory_item
{
    annotations_directory_item() : class_annotations_off(0), fields_size(0),
        annotated_methods_size(0), annotated_parameters_size(0),
        field_annotations(nullptr), method_annotations(nullptr),
        parameter_annotation(nullptr) {}

    /*
      ���ļ���ͷ��ֱ���ڸ�����������ע�͵�ƫ�������������û���κ�ֱ��ע�ͣ����ֵΪ 0��
      ��ƫ���������Ϊ����ֵ��Ӧ���ǵ� data ������ĳ��λ�õ�ƫ���������ݸ�ʽ�����ĵ�
      ��annotation_set_item��ָ����
     */
    u4 class_annotations_off;
    u4 fields_size;                // ������ע�͵��ֶ�������
    u4 annotated_methods_size;     // ������ע�͵ķ���������
    u4 annotated_parameters_size;  // ������ע�͵ķ��������б��������
    /*
      Optional���������ֶε�ע���б����б��е�Ԫ�ر��밴 field_idx �������������
     */
    field_annotation* field_annotations;
    /*
      Optional��������������ע���б����б��е�Ԫ�ر��밴 method_idx �������������
     */
    method_annotation* method_annotations;
    /*
      Optional������������������ע���б����б��е�Ԫ�ر��밴 method_idx �������������
     */
    parameter_annotation* parameter_annotation;
};

inline void print_dex_header(header_item* dex_header) {
    printf("magic: ");
    Printer::print_hex_array(dex_header->magic, 8);
    printf("checksum: %d\n", dex_header->checksum);

    printf("signature: ");
    Printer::print_hex_array(dex_header->signature, 20);

    printf("file_size: %d\n", dex_header->file_size);
    printf("header_size: %d\n", dex_header->header_size);
    printf("endian_tag: %d\n", dex_header->endian_tag);
    printf("link_size: %d\n", dex_header->link_size);
    printf("link_off: %d\n", dex_header->link_off);
    printf("map_off: %d\n", dex_header->map_off);
    printf("string_ids_size: %d\n", dex_header->string_ids_size);
    printf("string_ids_off: %d\n", dex_header->string_ids_off);
    printf("type_ids_size: %d\n", dex_header->type_ids_size);
    printf("type_ids_off: %d\n", dex_header->type_ids_off);
    printf("proto_ids_size: %d\n", dex_header->proto_ids_size);
    printf("proto_ids_off: %d\n", dex_header->proto_ids_off);
    printf("field_ids_size: %d\n", dex_header->field_ids_size);
    printf("field_ids_off: %d\n", dex_header->field_ids_off);
    printf("method_ids_size: %d\n", dex_header->method_ids_size);
    printf("method_ids_off: %d\n", dex_header->method_ids_off);
    printf("class_defs_size: %d\n", dex_header->class_defs_size);
    printf("class_defs_off: %d\n", dex_header->class_defs_off);
    printf("data_size: %d\n", dex_header->data_size);
    printf("data_off: %d\n", dex_header->data_off);
}

#endif // !DEX_FILE_H
