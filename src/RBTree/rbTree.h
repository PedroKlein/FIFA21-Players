#pragma once

#include <memory>
#include <vector>

enum class Color
{
    Red,
    Black
};

template <typename T>
struct Node
{
    T key;
    Color color;
    std::unique_ptr<Node<T>> left;
    std::unique_ptr<Node<T>> right;
    Node<T> *parent;

    Node(const T &key) : key{key}, parent{nullptr}, color{Color::Red} {}
};

template <typename T>
class RBTree
{
private:
    std::unique_ptr<Node<T>> root;
    size_t size{};

public:
    Node<T> *search(const T &key)
    {
        return search(root.get(), key);
    }

    // doesn't insert repeated keys
    void insert(const T &key)
    {
        auto z = std::make_unique<Node<T>>(key);
        insert(std::move(z));
    }

    void deleteKey(const T &key)
    {
        auto z = search(key);
        deleteKey(z);
    }

    size_t getSize()
    {
        return this->size;
    }

    typename std::vector<T> getOderedVector()
    {
        std::vector<T> res;
        fillInOrdered(root.get(), res);
        return res;
    }

private:
    void fillInOrdered(Node<T> *node, std::vector<T> &vec)
    {

        if (!node)
            return;

        fillInOrdered(node->left.get(), vec);

        vec.emplace_back(node->key);

        fillInOrdered(node->right.get(), vec);
    }

    void leftRotate(std::unique_ptr<Node<T>> &&x)
    {
        auto y = std::move(x->right);
        x->right = std::move(y->left);
        if (x->right)
        {
            x->right->parent = x.get();
        }
        y->parent = x->parent;
        auto xp = x->parent;
        if (!xp)
        {
            auto px = x.release();
            root = std::move(y);
            root->left = std::unique_ptr<Node<T>>(px);
            root->left->parent = root.get();
        }
        else if (x == xp->left)
        {
            auto px = x.release();
            xp->left = std::move(y);
            xp->left->left = std::unique_ptr<Node<T>>(px);
            xp->left->left->parent = xp->left.get();
        }
        else
        {
            auto px = x.release();
            xp->right = std::move(y);
            xp->right->left = std::unique_ptr<Node<T>>(px);
            xp->right->left->parent = xp->right.get();
        }
    }

    void rightRotate(std::unique_ptr<Node<T>> &&x)
    {
        auto y = std::move(x->left);
        x->left = std::move(y->right);
        if (x->left)
        {
            x->left->parent = x.get();
        }
        y->parent = x->parent;
        auto xp = x->parent;
        if (!xp)
        {
            auto px = x.release();
            root = std::move(y);
            root->right = std::unique_ptr<Node<T>>(px);
            root->right->parent = root.get();
        }
        else if (x == xp->left)
        {
            auto px = x.release();
            xp->left = std::move(y);
            xp->left->right = std::unique_ptr<Node<T>>(px);
            xp->left->right->parent = xp->left.get();
        }
        else
        {
            auto px = x.release();
            xp->right = std::move(y);
            xp->right->right = std::unique_ptr<Node<T>>(px);
            xp->right->right->parent = xp->right.get();
        }
    }

    Node<T> *search(Node<T> *x, const T &key)
    {
        if (!x || x->key == key)
        {
            return x;
        }
        if (key < x->key)
        {
            return search(x->left.get(), key);
        }
        else
        {
            return search(x->right.get(), key);
        }
    }

    void insert(std::unique_ptr<Node<T>> z)
    {
        Node<T> *y = nullptr;
        Node<T> *x = root.get();
        while (x)
        {
            y = x;
            if (z->key == x->key)
                return;
            if (z->key < x->key)
            {
                x = x->left.get();
            }
            else
            {
                x = x->right.get();
            }
        }
        z->parent = y;
        if (!y)
        {
            root = std::move(z);
            insertFixup(std::move(root));
        }
        else if (z->key < y->key)
        {
            y->left = std::move(z);
            insertFixup(std::move(y->left));
        }
        else
        {
            y->right = std::move(z);
            insertFixup(std::move(y->right));
        }
        size++;
    }

    void insertFixup(std::unique_ptr<Node<T>> &&z)
    {
        auto zp = z->parent;
        while (zp && zp->color == Color::Red)
        {
            auto zpp = zp->parent;
            if (zp == zpp->left.get())
            {
                auto y = zpp->right.get();
                if (y && y->color == Color::Red)
                {
                    zp->color = Color::Black;
                    y->color = Color::Black;
                    zpp->color = Color::Red;
                    zp = zpp->parent;
                }
                else
                {
                    if (z == zp->right)
                    {
                        leftRotate(std::move(zpp->left));
                        zp = zpp->left.get();
                    }
                    zp->color = Color::Black;
                    zpp->color = Color::Red;
                    auto zppp = zpp->parent;
                    if (!zppp)
                    {
                        rightRotate(std::move(root));
                    }
                    else if (zpp == zppp->left.get())
                    {
                        rightRotate(std::move(zppp->left));
                    }
                    else
                    {
                        rightRotate(std::move(zppp->right));
                    }
                }
            }
            else
            {
                auto y = zpp->left.get();
                if (y && y->color == Color::Red)
                {
                    zp->color = Color::Black;
                    y->color = Color::Black;
                    zpp->color = Color::Red;
                    zp = zpp->parent;
                }
                else
                {
                    if (z == zp->left)
                    {
                        rightRotate(std::move(zpp->right));
                        zp = zpp->right.get();
                    }
                    zp->color = Color::Black;
                    zpp->color = Color::Red;
                    auto zppp = zpp->parent;
                    if (!zppp)
                    {
                        leftRotate(std::move(root));
                    }
                    else if (zpp == zppp->left.get())
                    {
                        leftRotate(std::move(zppp->left));
                    }
                    else
                    {
                        leftRotate(std::move(zppp->right));
                    }
                }
            }
        }
        root->color = Color::Black;
    }

    Node<T> *transplant(Node<T> *u, std::unique_ptr<Node<T>> &&v)
    {
        if (v)
        {
            v->parent = u->parent;
        }
        Node<T> *w = nullptr;
        if (!u->parent)
        {
            w = root.release();
            root = std::move(v);
        }
        else if (u == u->parent->left.get())
        {
            w = u->parent->left.release();
            u->parent->left = std::move(v);
        }
        else
        {
            w = u->parent->right.release();
            u->parent->right = std::move(v);
        }
        return w;
    }

    Node<T> *minimum(Node<T> *x)
    {
        if (!x)
        {
            return x;
        }
        while (x->left)
        {
            x = x->left.get();
        }
        return x;
    }

    void deleteKey(Node<T> *z)
    {
        if (!z)
        {
            return;
        }
        Color orig_color = z->color;
        Node<T> *x = nullptr;
        Node<T> *xp = nullptr;
        if (!z->left)
        {
            x = z->right.get();
            xp = z->parent;
            auto pz = transplant(z, std::move(z->right));
            auto upz = std::unique_ptr<Node<T>>(pz);
        }
        else if (!z->right)
        {
            x = z->left.get();
            xp = z->parent;
            auto pz = transplant(z, std::move(z->left));
            auto upz = std::unique_ptr<Node<T>>(pz);
        }
        else
        {
            auto y = minimum(z->right.get());
            orig_color = y->color;
            x = y->right.get();
            xp = y;
            if (y->parent == z)
            {
                if (x)
                {
                    x->parent = y;
                }
                auto pz = transplant(z, std::move(z->right));
                y->left = std::move(pz->left);
                y->left->parent = y;
                y->color = pz->color;
                auto upz = std::unique_ptr<Node<T>>(pz);
            }
            else
            {
                xp = y->parent;
                auto py = transplant(y, std::move(y->right));
                py->right = std::move(z->right);
                py->right->parent = py;
                auto upy = std::unique_ptr<Node<T>>(py);
                auto pz = transplant(z, std::move(upy));
                py->left = std::move(pz->left);
                py->left->parent = py;
                py->color = pz->color;
                auto upz = std::unique_ptr<Node<T>>(pz);
            }
        }
        if (orig_color == Color::Black)
        {
            deleteFixup(x, xp);
        }
    }

    void deleteFixup(Node<T> *x, Node<T> *xp)
    {
        while (x != root.get() && (!x || x->color == Color::Black))
        {
            if (x == xp->left.get())
            {
                Node<T> *w = xp->right.get();
                if (w && w->color == Color::Red)
                {
                    w->color = Color::Black;
                    xp->color = Color::Red;
                    auto xpp = xp->parent;
                    if (!xpp)
                    {
                        leftRotate(std::move(root));
                    }
                    else if (xp == xpp->left.get())
                    {
                        leftRotate(std::move(xpp->left));
                    }
                    else
                    {
                        leftRotate(std::move(xpp->right));
                    }
                    w = xp->right.get();
                }
                if (w && (!w->left || w->left->color == Color::Black) && (!w->right || w->right->color == Color::Black))
                {
                    w->color = Color::Red;
                    x = xp;
                    xp = xp->parent;
                }
                else if (w)
                {
                    if (!w->right || w->right->color == Color::Black)
                    {
                        w->left->color = Color::Black;
                        w->color = Color::Red;
                        auto wp = w->parent;
                        if (!wp)
                        {
                            rightRotate(std::move(root));
                        }
                        else if (w == wp->left.get())
                        {
                            rightRotate(std::move(wp->left));
                        }
                        else
                        {
                            rightRotate(std::move(wp->right));
                        }
                        w = xp->right.get();
                    }
                    w->color = xp->color;
                    xp->color = Color::Black;
                    w->right->color = Color::Black;
                    auto xpp = xp->parent;
                    if (!xpp)
                    {
                        leftRotate(std::move(root));
                    }
                    else if (xp == xpp->left.get())
                    {
                        leftRotate(std::move(xpp->left));
                    }
                    else
                    {
                        leftRotate(std::move(xpp->right));
                    }
                    x = root.get();
                }
                else
                {
                    x = root.get();
                }
            }
            else
            {
                Node<T> *w = xp->left.get();
                if (w && w->color == Color::Red)
                {
                    w->color = Color::Black;
                    xp->color = Color::Red;
                    auto xpp = xp->parent;
                    if (!xpp)
                    {
                        rightRotate(std::move(root));
                    }
                    else if (xp == xpp->left.get())
                    {
                        rightRotate(std::move(xpp->left));
                    }
                    else
                    {
                        rightRotate(std::move(xpp->right));
                    }
                    w = xp->left.get();
                }
                if (w && (!w->left || w->left->color == Color::Black) && (!w->right || w->right->color == Color::Black))
                {
                    w->color = Color::Red;
                    x = xp;
                    xp = xp->parent;
                }
                else if (w)
                {
                    if (!w->left || w->left->color == Color::Black)
                    {
                        w->right->color = Color::Black;
                        w->color = Color::Red;
                        auto wp = w->parent;
                        if (!wp)
                        {
                            leftRotate(std::move(root));
                        }
                        else if (w == wp->left.get())
                        {
                            leftRotate(std::move(wp->left));
                        }
                        else
                        {
                            leftRotate(std::move(wp->right));
                        }
                        w = xp->left.get();
                    }
                    w->color = xp->color;
                    xp->color = Color::Black;
                    w->left->color = Color::Black;
                    auto xpp = xp->parent;
                    if (!xpp)
                    {
                        rightRotate(std::move(root));
                    }
                    else if (xp == xpp->left.get())
                    {
                        rightRotate(std::move(xpp->left));
                    }
                    else
                    {
                        rightRotate(std::move(xpp->right));
                    }
                    x = root.get();
                }
                else
                {
                    x = root.get();
                }
            }
        }
        if (x)
        {
            x->color = Color::Black;
        }
    }
};