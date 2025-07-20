#pragma once
#include <string>

class EncryptMD5
{
public:
    EncryptMD5()
    {
        reset();
    }

    // �����ַ�����MD5ֵ
    std::string compute(const std::string& input);

private:
    // �ڲ�������
    void transform(const uint8_t block[64]);

    // �����������
    void update(const uint8_t* input, size_t length);

    // ��ɼ��㲢���ؽ��
    void final(uint8_t digest[16]);

    // ����MD5����״̬
    void reset();

private:
    uint32_t state[4];  // MD5���ĸ�״̬�Ĵ���(A, B, C, D)
    uint8_t buffer[64]; // 512λ�����뻺����
    uint64_t count[2];  // 64λ��λ������
};
