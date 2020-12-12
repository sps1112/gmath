#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include "Standard.h"

namespace gmath
{
    class Vector
    {
    private:
        bool isInitialized = false;

    public:
        float **list;
        float *array[4];
        int size;
        Vector() // Standard Constructor
        {
            list = NULL;
            //Log("Constructor");
        }

        void PrintList()
        {
            std::cout << &list << "  " << list << "  " << *list << "   " << **list << "  " << size << std::endl;
            std::cout << &list << "  " << list + 1 << "  " << *(list + 1) << "   " << **(list + 1) << "  " << size << std::endl;
            std::cout << &list << "  " << list + 2 << "  " << *(list + 2) << "   " << **(list + 2) << "  " << size << std::endl;
        }

        ~Vector() // Destructor
        {
            if (list)
            {
                if (!isInitialized)
                {
                    Log("Not initially defined");
                    SetDefault();
                }
                //PrintList();
                delete[] list;
                list = NULL;
            }
        }

        void SetToList(float **localPointer)
        {
            isInitialized = true;
            list = localPointer;
        }

        template <typename T>
        float GetVal(const T &b, int index)
        {
            return **(b.list + index);
            // return *(b.array[index]);
        }

        template <typename T>
        float *GetVar(const T &b, int index)
        {
            return *(b.list + index);
            // return b.array[index];
        }

        void SetVal(int index, float value)
        {
            **(list + index) = value;
            // *(array[index]) = value;
        }

        /* Vector(const Vector &b) // Copy COnstructor
        {
            Log("Copy Constructor");
            std::cout << &array[0] << std::endl;
            Log(*b.array[0]);
            Log(*array[0]);
            Log(size);
            deepCopy(b);
        }*/

        void SetDefault() // Set default values
        {
            Log("Setting Default Value");
            delete[] list;
            list = NULL;
            list = new float *[4];
            float a = 5.0;
            for (int i = 0; i < 4; i++)
            {
                *(list + i) = &a;
            }
        }

        void deepCopy(const Vector &b)
        {
            if (!isInitialized)
            {
                SetDefault();
            }
            Log("Calling deepCopy");
            if (b.array)
            {
                Log("Inside If");
                for (int i = 0; i < b.size; i++)
                {
                    Log("Inside loop");
                    std::cout << i << "  " << *(b.array[i]) << std::endl;
                    SetVal(i, GetVal(b, i));
                    // *(array[i]) = *(b.array[i]);
                }
            }
        }

        void SetToArray(float *x) // Vec1
        {
            size = 1;
            array[0] = x;
        }

        void SetToArray(float *x, float *y) // Vec2
        {
            size = 2;
            array[0] = x;
            array[1] = y;
        }

        void SetToArray(float *x, float *y, float *z) // Vec3
        {
            if (list == NULL)
            {
                SetDefault();
            }
            size = 3;
            array[0] = x;
            array[1] = y;
            array[2] = z;
        }

        void SetToArray(float *x, float *y, float *z, float *w) // Vec4
        {
            size = 4;
            array[0] = x;
            array[1] = y;
            array[2] = z;
            array[3] = w;
        }

        void operator=(const Vector &b) // Assignment Operator
        {
            // Log("Assignment Operator");
            for (int i = 0; i < size; i++)
            {
                SetVal(i, GetVal(b, i));
                //*(array[i]) = *(b.array[i]);
            }
        }

        template <typename T>
        T &operator=(const T &b) // Other Assignment Operator
        {
            // Log("Assignment Operator-2");
            if (this != &b)
            {
                deepCopy(b);
            }
            return *this;
        }

        template <typename T>
        T operator+(const T &b) // Vec A + Vec B
        {
            T c;
            for (int i = 0; i < size; i++)
            {
                c.SetVal(i, (GetVal(*this, i) + GetVal(b, i)));
                // *(c.array[i]) = *(this->array[i]) + *(b.array[i]);
            }
            return c;
        }

        template <typename T>
        T operator-(const T &b) // Vec A - Vec B
        {
            T c;
            for (int i = 0; i < size; i++)
            {
                c.SetVal(i, (GetVal(*this, i) - GetVal(b, i)));
                // *(c.array[i]) = *(this->array[i]) - *(b.array[i]);
            }
            return c;
        }

        template <typename T>
        friend std::ostream &operator<<(std::ostream &output, const T &b) //Output vec
        {
            output << "(";
            T c = T();
            for (int i = 0; i < b.size; i++)
            {
                output << c.GetVal(b, i);
                // output << *(b.array[i]);
                if (i != b.size - 1)
                {
                    output << ",";
                }
            }
            output << ")";
            return output;
        }

        template <typename T>
        friend std::istream &operator>>(std::istream &input, T &b) // Input Vec
        {
            T c = T();
            float *temp;
            for (int i = 0; i < b.size; i++)
            {
                temp = c.GetVar(b, i);
                input >> *temp;
                // input >> *(b.array[i]);
            }
            return input;
        }

        template <typename T>
        bool operator==(const T &b) // check Vec A == Vec B
        {
            bool status = true;
            for (int i = 0; i < size; i++)
            {
                //if (*this->array[i] != *b.array[i])
                if (GetVal(*this, i) != GetVal(b, i))
                {
                    status = false;
                    break;
                }
            }
            return status;
        }

        template <typename T>
        bool operator!=(const T &b) // Check Vec A != Vec B
        {
            bool status = true;
            for (int i = 0; i < size; i++)
            {
                // if (*this->array[i] != *b.array[i])
                if (GetVal(*this, i) != GetVal(b, i))
                {
                    status = false;
                    break;
                }
            }
            return !status;
        }

        float GetSqrMagnitude() // Get (|Vec A|)^2
        {
            float mag = 0;
            for (int i = 0; i < size; i++)
            {
                mag += (GetVal(*this, i)) * (GetVal(*this, i));
                // mag += ((*(this->array[i])) * (*(this->array[i])));
            }
            return mag;
        }

        float GetMagnitude() // Get |Vec A|
        {
            return sqrt(GetSqrMagnitude());
        }

        void Normalize() // Set Vec A = Vec A/ (|Vec A|)
        {
            float mag = GetMagnitude();
            if (mag != 0)
            {
                for (int i = 0; i < size; i++)
                {
                    SetVal(i, GetVal(*this, i) / mag);
                    // *(this->array[i]) /= mag;
                }
            }
        }

        template <typename T>
        T ConvertToVector(T b) // Convert VectorN to VectorM where N,M={1,2,3,4}
        {
            for (int i = 0; i < Min(size, b.size); i++)
            {
                // *b.array[i] = *array[i];
            }
            return b;
        }
    };

    //Overloaded Operators and Other Functions

    template <typename T>
    T operator+(const T &a) // +VecA
    {
        T c;
        for (int i = 0; i < a.size; i++)
        {
            c.SetVal(i, c.GetVal(a, i));
            // *(c.array[i]) = +*(a.array[i]);
        }
        return c;
    }

    template <typename T>
    T operator-(const T &a) // -VecA
    {
        T c;
        for (int i = 0; i < a.size; i++)
        {
            c.SetVal(i, -c.GetVal(a, i));
            // *(c.array[i]) = -*(a.array[i]);
        }
        return c;
    }

    template <typename T>
    T operator*(const float &b, const T &a) //  float x* Vec A
    {
        //a.PrintList();
        T c;
        for (int i = 0; i < a.size; i++)
        {
            c.SetVal(i, c.GetVal(a, i) * b);
            // *(c.array[i]) = *(a.array[i]) * b;
        }
        return c;
    }

    template <typename T>
    T operator*(const T &a, const float &b) //  Vec A*float x
    {
        return operator*(b, a);
    }

    template <typename T>
    T operator/(const T &a, const float &b) //  Vec A / float x
    {
        T c;
        for (int i = 0; i < a.size; i++)
        {
            c.SetVal(i, c.GetVal(a, i) / b);
            // *(c.array[i]) = *(a.array[i]) / b;
        }
        return c;
    }

    template <typename T>
    T GetDisplacement(const T &a, const T &b) // returns Displacment from a to b
    {
        T c;
        for (int i = 0; i < a.size; i++)
        {
            c.SetVal(i, (c.GetVal(b, i) - c.GetVal(a, i)));
            // *(c.array[i]) = *(b.array[i]) - *(a.array[i]);
        }
        return c;
    }

    template <typename T>
    float GetDistance(const T &a, const T &b) // returns Distance from a to b
    {
        T c = GetDisplacement(a, b);
        return c.GetMagnitude();
    }

    template <typename T>
    float GetSqrDistance(const T &a, const T &b) // returns Distance from a to b
    {
        T c = GetDisplacement(a, b);
        return c.GetSqrMagnitude();
    }

    template <typename T>
    T Lerp(const T &a, const T &b, float range) // Lerps between VecA and VecB by range(0<=range<=1)
    {
        range = Clamp(0, 1, range);
        T c = GetDisplacement(a, b);
        for (int i = 0; i < a.size; i++)
        {
            c.SetVal(i, c.GetVal(a, i) + range * c.GetVal(c, i));
            // *c.array[i] = *a.array[i] + (range) * (*c.array[i]);
        }
        return c;
    }

    template <typename T>
    T GetMax(const T &a, const T &b) // Get Vec by Max components of A and B
    {
        T c;
        for (int i = 0; i < a.size; i++)
        {
            c.SetVal(i, Max(c.GetVal(a, i), c.GetVal(b, i)));
            // *c.array[i] = Max(*a.array[i], *b.array[i]);
        }
        return c;
    }

    template <typename T>
    T GetMin(const T &a, const T &b) // Get Vec by Min components of A and B
    {
        T c = T();
        for (int i = 0; i < a.size; i++)
        {
            c.SetVal(i, Min(c.GetVal(a, i), c.GetVal(b, i)));
            // *c.array[i] = Min(*a.array[i], *b.array[i]);
        }
        return c;
    }

    template <typename T>
    T GetNormalized(const T &a) // returns VecA/(|VecA|)
    {
        T c = T();
        c = a;
        float mag = 0;
        for (int i = 0; i < a.size; i++)
        {
            mag += (c.GetVal(a, i)) * (c.GetVal(a, i));
            // mag += (*a.array[i]) * (*a.array[i]);
        }
        mag = sqrt(mag);
        if (mag != 0)
        {
            for (int i = 0; i < a.size; i++)
            {
                c.SetVal(i, c.GetVal(a, i) / mag);
                // *c.array[i] = (*a.array[i]) / mag;
            }
        }
        return c;
    }

    template <typename T>
    float DotProduct(const T &a, const T &b) // Vec A . Vec B
    {
        float c = 0;
        T d = T();
        for (int i = 0; i < a.size; i++)
        {
            c += d.GetVal(a, i) * d.GetVal(b, i);
            // c += *(a.array[i]) * *(b.array[i]);
        }
        return c;
    }

    template <typename T>
    T DotVector(const T &a, const T &b) // Vec formed by the dot product components
    {
        T c = T();
        for (int i = 0; i < a.size; i++)
        {
            c.SetVal(i, c.GetVal(a, i) * c.GetVal(b, i));
            // *(c.array[i]) = *(a.array[i]) * *(b.array[i]);
        }
        return c;
    }

    //VECTOR1 Class
    class Vector1 : public Vector
    {
    private:
        // Private Variables
    public:
        float x;
        Vector1(float X = 0)
        {
            x = X;

            float **localList = NULL;
            localList = new float *[1];
            *(localList + 0) = &x;
            SetToList(localList);
            SetToArray(&x);
        }
    };

    //VECTOR2 Class
    class Vector2 : public Vector
    {
    private:
        // Private Variables
    public:
        float x;
        float y;
        Vector2(float X = 0, float Y = 0)
        {
            x = X;
            y = Y;

            float **localList = NULL;
            localList = new float *[2];
            *(localList + 0) = &x;
            *(localList + 1) = &y;
            SetToList(localList);
            SetToArray(&x, &y);
        }
    };

    //VECTOR3 Class
    class Vector3 : public Vector
    {
    private:
        // Private Variables
    public:
        float x;
        float y;
        float z;
        Vector3(float X = 0, float Y = 0, float Z = 0)
        {
            x = X;
            y = Y;
            z = Z;
            float **localList = NULL;
            localList = new float *[3];
            *(localList + 0) = &x;
            *(localList + 1) = &y;
            *(localList + 2) = &z;
            SetToList(localList);
            SetToArray(&x, &y, &z);
        }

        Vector3 Cross(Vector3 a, Vector3 b);
    };

    //Vector4 Class
    class Vector4 : public Vector
    {
    private:
        // Private Variables
    public:
        float x;
        float y;
        float z;
        float w;
        Vector4(float X = 0, float Y = 0, float Z = 0, float W = 0)
        {
            x = X;
            y = Y;
            z = Z;
            w = W;

            float **localList = NULL;
            localList = new float *[4];
            *(localList + 0) = &x;
            *(localList + 1) = &y;
            *(localList + 2) = &z;
            *(localList + 3) = &w;
            SetToList(localList);

            SetToArray(&x, &y, &z, &w);
        }
    };

    //STANDARD VECTORS
    /*Vector1 one1 = Vector1(1);
    Vector1 zero1 = Vector1(0);

    Vector2 one2 = Vector2(1, 1);
    Vector2 zero2 = Vector2(0, 0);
    Vector2 up2 = Vector2(0, 1);
    Vector2 down2 = Vector2(0, -1);
    Vector2 left2 = Vector2(-1, 0);
    Vector2 right2 = Vector2(1, 0);

    Vector3 one3 = Vector3(1, 1, 1);
    Vector3 zero3 = Vector3(0, 0, 0);
    Vector3 up3 = Vector3(0, 1, 0);
    Vector3 down3 = Vector3(0, -1, 0);
    Vector3 left3 = Vector3(-1, 0, 0);
    Vector3 right3 = Vector3(1, 0, 0);
    Vector3 front3 = Vector3(0, 0, -1);
    Vector3 back3 = Vector3(0, 0, 1);

    Vector4 one4 = Vector4(1, 1, 1, 1);
    Vector4 zero4 = Vector4(0, 0, 0, 0);*/

    //Class functions

    Vector3 Cross(const Vector3 &a, const Vector3 &b)
    {
        Vector3 c;
        c.x = a.y * b.z - a.z * b.y;
        c.y = a.z * b.x - a.x * b.z;
        c.z = a.x * b.y - a.y * b.x;
        return c;
    }

    //Rotation Functions

    /*template <typename T>
    float GetAngle(T a, T b)
    {
        Log("same type");
        if (a.size == 2)
        {
            return GetAngle(a.ConvertToVector(zero3), b.ConvertToVector(zero3));
        }
        else
        {
            T cross = Cross(a, b);
            cross = cross / (a.GetMagnitude() * b.GetMagnitude());
            T unit = GetNormalized(cross);
            return GetAsin(cross.x / unit.x);
        }
    }

    template <typename T1, typename T2>
    float GetAngle(T1 a, T2 b)
    {
        Log("different type");
        return (GetAngle(a.ConvertToVector(zero3), b.ConvertToVector(zero3)));
    }*/

} // namespace gmath

#endif