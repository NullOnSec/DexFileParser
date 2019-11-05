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

struct header_item {
    u1 magic[8];        // ħ����
    u1 checksum;        // �ļ�ʣ�����ݣ��� magic �ʹ��ֶ�֮�����������)�� adler32 У��ͣ����ڼ���ļ��������
    u1 signature[20];   // �ļ�ʣ�����ݣ��� magic��checksum �ʹ��ֶ�֮�����������)�� SHA-1 ǩ������ϣ)�����ڶ��ļ�����Ψһ��ʶ��
    u4 file_size;       // �����ļ���������ͷ)�Ĵ�С�����ֽ�Ϊ��λ��
    u4 header_size;     // ��ͷ����������)�Ĵ�С�����ֽ�Ϊ��λ����һ����������һ���̶ȵ����/��ǰ�����ԣ��������ø�ʽʧЧ��
    u4 endian_tag;      // �ֽ����ǡ�
    u4 link_size;       // �������εĴ�С��������ļ�δ���о�̬���ӣ����ֵΪ 0��
    u4 link_off;        // ���ļ���ͷ���������ε�ƫ��������� link_size == 0�����ֵΪ 0����ƫ���������Ϊ����ֵ)Ӧ���ǵ� link_data ���ε�ƫ������
    u4 map_off;         // ���ļ���ͷ��ӳ�����ƫ��������ƫ����������Ϊ����)Ӧ���ǵ� data ���ε�ƫ������
    u4 string_ids_size; // �ַ�����ʶ���б��е��ַ���������
    u4 string_ids_off;  // ���ļ���ͷ���ַ�����ʶ���б��ƫ��������� string_ids_size == 0���������)�����ֵΪ 0����ƫ���������Ϊ����ֵ)Ӧ���ǵ� string_ids ���ο�ͷ��ƫ������
    u4 type_ids_size;   // ���ͱ�ʶ���б��е�Ԫ�����������Ϊ 65535��
    u4 type_ids_off;    // ���ļ���ͷ�����ͱ�ʶ���б��ƫ��������� type_ids_size == 0���������)�����ֵΪ 0����ƫ���������Ϊ����ֵ)Ӧ���ǵ� type_ids ���ο�ͷ��ƫ������
    u4 proto_ids_size;  // ԭ�ͱ�ʶ���б��е�Ԫ�����������Ϊ 65535��
    u4 proto_ids_off;   // ���ļ���ͷ��ԭ�ͱ�ʶ���б��ƫ��������� proto_ids_size == 0���������)�����ֵΪ 0����ƫ���������Ϊ����ֵ)Ӧ���ǵ� proto_ids ���ο�ͷ��ƫ������
    u4 field_ids_size;  // �ֶα�ʶ���б��е�Ԫ��������
    u4 field_ids_off;   // ���ļ���ͷ���ֶα�ʶ���б��ƫ��������� field_ids_size == 0�����ֵΪ 0����ƫ���������Ϊ����ֵ)Ӧ���ǵ� field_ids ���ο�ͷ��ƫ������
    u4 method_ids_size; // ������ʶ���б��е�Ԫ��������
    u4 method_ids_off;  // ���ļ���ͷ��������ʶ���б��ƫ��������� method_ids_size == 0�����ֵΪ 0����ƫ���������Ϊ����ֵ)Ӧ���ǵ� method_ids ���ο�ͷ��ƫ������
    u4 class_defs_size; // �ඨ���б��е�Ԫ��������
    u4 class_defs_off;  // ���ļ���ͷ���ඨ���б��ƫ��������� class_defs_size == 0���������)�����ֵΪ 0����ƫ���������Ϊ����ֵ)Ӧ���ǵ� class_defs ���ο�ͷ��ƫ������
    u4 data_size;       // data ���εĴ�С�����ֽ�Ϊ��λ)������ֵ������ sizeof(uint) ��ż������
    u4 data_off;        // ���ļ���ͷ�� data ���ο�ͷ��ƫ������
};

struct map_item
{
    u2 type;   // ������͡�
    u2 unused; //��δʹ�á�
    u4 size;   // ��ָ��ƫ�������ҵ�����������
    u4 offset; // ���ļ���ͷ��������ƫ������
};

struct map_list
{
    u4 size;          // �б�Ĵ�С������Ŀ����ʾ����
    map_item list[1]; // �б��Ԫ�ء�
};


struct string_id_item
{
    u4 string_data_off; // ���ļ���ͷ��������ַ������ݵ�ƫ��������ƫ����Ӧ���ǵ� data ������ĳ��λ�õ�ƫ������
};

struct type_id_item
{
    u4 descriptor_idx; // �����������ַ����� string_ids �б��е����������ַ�������������Ķ���� TypeDescriptor ���﷨��
};

struct proto_id_item
{
    u4 shorty_ids;      // ��ԭ�͵ļ��ʽ�������ַ����� string_ids �б��е����������ַ�������������Ķ���� ShortyDescriptor ���﷨�����ұ��������ķ������ͺͲ������Ӧ��
    u4 return_type_idx; // ��ԭ�͵ķ������͵� type_ids �б��е�������
    u4 parameters_off;  // ���ļ���ͷ����ԭ�͵Ĳ��������б��ƫ�����������ԭ��û�в��������ֵΪ 0����ƫ���������Ϊ����ֵ��Ӧ��λ�� data �����У������е�����Ӧ���������С�"type_list"��ָ���ĸ�ʽ�����⣬���ö��б��е����� void �����κ����á�
};

struct DexFile
{
    
};

inline void print_dex_header(header_item* dexHeader) {
    printf("header_item:\n");

    printf("magic: ");
    Printer::print_hex_array(dexHeader->magic, 8);
    printf("checksum: %d\n", dexHeader->checksum);

    printf("signature: ");
    Printer::print_hex_array(dexHeader->signature, 20);

    printf("file_size: %d\n", dexHeader->file_size);
    printf("header_size: %d\n", dexHeader->header_size);
    printf("endian_tag: %d\n", dexHeader->endian_tag);
    printf("link_size: %d\n", dexHeader->link_size);
    printf("link_off: %d\n", dexHeader->link_off);
    printf("map_off: %d\n", dexHeader->map_off);
    printf("string_ids_size: %d\n", dexHeader->string_ids_size);
    printf("string_ids_off: %d\n", dexHeader->string_ids_off);
    printf("type_ids_size: %d\n", dexHeader->type_ids_size);
    printf("type_ids_off: %d\n", dexHeader->type_ids_off);
    printf("proto_ids_size: %d\n", dexHeader->proto_ids_size);
    printf("proto_ids_off: %d\n", dexHeader->proto_ids_off);
    printf("field_ids_size: %d\n", dexHeader->field_ids_size);
    printf("field_ids_off: %d\n", dexHeader->field_ids_off);
    printf("method_ids_size: %d\n", dexHeader->method_ids_size);
    printf("method_ids_off: %d\n", dexHeader->method_ids_off);
    printf("class_defs_size: %d\n", dexHeader->class_defs_size);
    printf("class_defs_off: %d\n", dexHeader->class_defs_off);
    printf("data_size: %d\n", dexHeader->data_size);
    printf("data_off: %d\n", dexHeader->data_off);
}

#endif // !DEX_FILE_H
