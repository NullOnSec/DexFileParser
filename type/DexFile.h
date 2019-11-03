#ifndef DEXFILE_H_
#define DEXFILE_H_

#include <cstdint>
#include <iostream>

#include "util/Format.h"

using namespace std;

typedef uint8_t   u1;
typedef uint16_t  u2;
typedef uint32_t  u4;
typedef uint64_t  u8;
typedef int8_t    s1;
typedef int16_t   s2;
typedef int32_t   s4;
typedef int64_t   s8;

/* header_item */
struct DexHeader {
	u1 magic[8];        /* ħ�� */
	u1 checksum;        /* �ļ�ʣ�����ݣ��� magic �ʹ��ֶ�֮����������ݣ��� adler32 У��ͣ����ڼ���ļ������ */
	u1 signature[20];   /* �ļ�ʣ�����ݣ��� magic��checksum �ʹ��ֶ�֮����������ݣ��� SHA-1 ǩ������ϣ�������ڶ��ļ�����Ψһ��ʶ */
	u4 file_size;       /* �����ļ���������ͷ���Ĵ�С�����ֽ�Ϊ��λ */
	u4 header_size;     /* ��ͷ���������Σ��Ĵ�С�����ֽ�Ϊ��λ����һ����������һ���̶ȵ����/��ǰ�����ԣ��������ø�ʽʧЧ */
	u4 endian_tag;      /* �ֽ����� */
	u4 link_size;       /* �������εĴ�С��������ļ�δ���о�̬���ӣ����ֵΪ 0 */
	u4 link_off;        /* ���ļ���ͷ���������ε�ƫ��������� link_size == 0�����ֵΪ 0����ƫ���������Ϊ����ֵ��Ӧ���ǵ� link_data ���ε�ƫ���� */
	u4 map_off;         /* ���ļ���ͷ��ӳ�����ƫ��������ƫ����������Ϊ���㣩Ӧ���ǵ� data ���ε�ƫ���� */
	u4 string_ids_size; /* �ַ�����ʶ���б��е��ַ������� */
	u4 string_ids_off;  /* ���ļ���ͷ���ַ�����ʶ���б��ƫ��������� string_ids_size == 0����������������ֵΪ 0����ƫ���������Ϊ����ֵ��Ӧ���ǵ� string_ids ���ο�ͷ��ƫ���� */
	u4 type_ids_size;   /* ���ͱ�ʶ���б��е�Ԫ�����������Ϊ 65535 */
	u4 type_ids_off;    /* ���ļ���ͷ�����ͱ�ʶ���б��ƫ��������� type_ids_size == 0����������������ֵΪ 0����ƫ���������Ϊ����ֵ��Ӧ���ǵ� type_ids ���ο�ͷ��ƫ���� */
	u4 proto_ids_size;  /* ԭ�ͱ�ʶ���б��е�Ԫ�����������Ϊ 65535 */
	u4 proto_ids_off;   /* ���ļ���ͷ��ԭ�ͱ�ʶ���б��ƫ��������� proto_ids_size == 0����������������ֵΪ 0����ƫ���������Ϊ����ֵ��Ӧ���ǵ� proto_ids ���ο�ͷ��ƫ���� */
	u4 field_ids_size;  /* �ֶα�ʶ���б��е�Ԫ������ */
	u4 field_ids_off;   /* ���ļ���ͷ���ֶα�ʶ���б��ƫ��������� field_ids_size == 0�����ֵΪ 0����ƫ���������Ϊ����ֵ��Ӧ���ǵ� field_ids ���ο�ͷ��ƫ���� */
	u4 method_ids_size; /* ������ʶ���б��е�Ԫ������ */
	u4 method_ids_off;  /* ���ļ���ͷ��������ʶ���б��ƫ��������� method_ids_size == 0�����ֵΪ 0����ƫ���������Ϊ����ֵ��Ӧ���ǵ� method_ids ���ο�ͷ��ƫ���� */
	u4 class_defs_size; /* �ඨ���б��е�Ԫ������ */
	u4 class_defs_off;  /* ���ļ���ͷ���ඨ���б��ƫ��������� class_defs_size == 0����������������ֵΪ 0����ƫ���������Ϊ����ֵ��Ӧ���ǵ� class_defs ���ο�ͷ��ƫ���� */
	u4 data_size;       /* data ���εĴ�С�����ֽ�Ϊ��λ��������ֵ������ sizeof(uint) ��ż���� */
	u4 data_off;        /* ���ļ���ͷ�� data ���ο�ͷ��ƫ���� */
};

void printDexHeader(DexHeader* dexHeader) {
    printf("header_item:\n");

	cout << "magic: " << dexHeader->magic << endl;

	cout << "checksum: " << dexHeader->checksum << endl;
	cout << "signature: " << dexHeader->signature << endl;
	cout << "file_size: " << dexHeader->file_size << endl;
	cout << "header_size: " << dexHeader->header_size << endl;
	cout << "endian_tag: " << dexHeader->endian_tag << endl;
	cout << "link_size: " << dexHeader->link_size << endl;
	cout << "link_off: " << dexHeader->link_off << endl;
	cout << "map_off: " << dexHeader->map_off << endl;
	cout << "string_ids_size: " << dexHeader->string_ids_size << endl;
	cout << "string_ids_off: " << dexHeader->string_ids_off << endl;
	cout << "type_ids_size: " << dexHeader->type_ids_size << endl;
	cout << "type_ids_off: " << dexHeader->type_ids_off << endl;
	cout << "proto_ids_size: " << dexHeader->proto_ids_size << endl;
	cout << "proto_ids_off: " << dexHeader->proto_ids_off << endl;
	cout << "field_ids_size: " << dexHeader->field_ids_size << endl;
	cout << "field_ids_off: " << dexHeader->field_ids_off << endl;
	cout << "method_ids_size: " << dexHeader->method_ids_size << endl;
	cout << "method_ids_off: " << dexHeader->method_ids_off << endl;
	cout << "class_defs_size: " << dexHeader->class_defs_size << endl;
	cout << "class_defs_off: " << dexHeader->class_defs_off << endl;
	cout << "data_size: " << dexHeader->data_size << endl;
	cout << "data_off: " << dexHeader->data_off << endl;
}

#endif // !DEXFILE_H_
