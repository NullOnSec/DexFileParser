#ifndef DEX_FILE_H
#define DEX_FILE_H

#include <cstdint>
#include <iostream>

#include "util/Formatter.h"
#include "util/Printer.h"

using namespace std;

typedef uint8_t   u1;
typedef uint16_t  u2;
typedef uint32_t  u4;
typedef uint64_t  u8;
typedef int8_t    s1;
typedef int16_t   s2;
typedef int32_t   s4;
typedef int64_t   s8;

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

struct header_item
{
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
    printf("size: %d\n", map_item->size);
    printf("offset: %d\n", map_item->offset);
}

struct map_list
{
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

struct DexFile
{
    header_item header;

};

inline void print_dex_header(header_item* dex_header) {
    printf("\nheader_item:\n");

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
