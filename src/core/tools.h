#ifndef TOOLS_H
#define TOOLS_H

#include <QBoxLayout>
#include <QCheckBox>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QLineEdit>
#include <QMouseEvent>
#include <QRadioButton>

class MainWindow;

class CustomEditor : public QFrame
{
    Q_OBJECT // NOLINT: Framework code, so can't fix this

public:
    template<typename T>
    explicit CustomEditor(int identifier, T *editorWidget, QWidget *buddyWidget = nullptr);

    CustomEditor(const CustomEditor &) = delete;
    auto operator=(const CustomEditor &) -> CustomEditor & = delete;
    CustomEditor(CustomEditor &&) = delete;
    auto operator=(CustomEditor &&) -> CustomEditor & = delete;

    ~CustomEditor() override;

    bool eventFilter(QObject *watched, QEvent *event) override;

    void addHintText(const QString &text);
    std::function<void()> callback = []() { /* Keep this empty. Otherwise we crash */ };

    QVBoxLayout *vLayout = new QVBoxLayout();
    QWidget *editor = nullptr;
    QLabel *label = nullptr;

    int id;

protected:
    void mouseReleaseEvent(QMouseEvent *event) override;

signals:
    void dataChanged(bool changed);

public slots:

    void updateSave(bool hasChanged);
    void updateStyle(bool hasChanged);

    virtual void updateData()
    {
        qDebug() << R"(Non-overloaded "updateData" was called!)";
    }

private:
    QWidget *buddy = nullptr;
};

class CustomLineEdit : public CustomEditor
{
    Q_OBJECT // NOLINT: Framework code, so can't fix this

public:
    explicit CustomLineEdit(int editorId, QWidget *buddyWidget = nullptr);

    QLineEdit *editor;

public slots: // NOLINT: False positive
    void updateSave(const QString &data);
    void updateData() override;
};

class CustomComboBox : public CustomEditor
{
    Q_OBJECT // NOLINT: Framework code, so can't fix this

public:
    explicit CustomComboBox(int editorId, QWidget *buddyWidget = nullptr);

    QComboBox *editor;

protected:
    void mouseReleaseEvent(QMouseEvent *event) override;

public slots: // NOLINT: False positive
    void updateSave(int data);
    void updateData() override;

private:
    QHash<double, int> indexes;
};

class CustomSpinBox : public CustomEditor
{
    Q_OBJECT // NOLINT: Framework code, so can't fix this

public:
    explicit CustomSpinBox(int editorId, QWidget *buddyWidget = nullptr);

    QDoubleSpinBox *editor;

public slots: // NOLINT: False positive
    void updateSave(double data);
    void updateData() override;
};

class CustomCheckBox : public CustomEditor
{
    Q_OBJECT // NOLINT: Framework code, so can't fix this

public:
    explicit CustomCheckBox(int editorId, const QString &text = "", QWidget *buddyWidget = nullptr);

    QCheckBox *editor;

protected:
    void mouseReleaseEvent(QMouseEvent *event) override;

public slots: // NOLINT: False positive
    virtual void updateSave(int data);
    void updateData() override;

private:
    QList<int> values = { 0, 1, 1 };
    QHash<int, Qt::CheckState> states = { { 0, Qt::Unchecked }, { 1, Qt::Checked } };
};

class CustomRadioButton : public CustomEditor
{
    Q_OBJECT // NOLINT: Framework code, so can't fix this

public:
    explicit CustomRadioButton(int editorId, const QString &text, QWidget *buddyWidget = nullptr);

    QRadioButton *editor;

protected:
    void mouseReleaseEvent(QMouseEvent *event) override;

public slots: // NOLINT: False positive
    void updateSave(bool data);
    void updateData() override;
};

class ItemComboBox : public CustomEditor
{
    Q_OBJECT // NOLINT: Framework code, so can't fix this

public:
    explicit ItemComboBox(int editorId, QWidget *buddyWidget = nullptr);

    QComboBox *editor;

protected:
    void mouseReleaseEvent(QMouseEvent *event) override;

public slots: // NOLINT: False positive
    void updateSave(int data);
    void updateData() override;
};

class PhoneComboBox : public CustomEditor
{
    Q_OBJECT // NOLINT: Framework code, so can't fix this

public:
    explicit PhoneComboBox(int editorId, QWidget *buddyWidget = nullptr);

    QComboBox *editor;

protected:
    void mouseReleaseEvent(QMouseEvent *event) override;

public slots: // NOLINT: False positive
    void updateSave(int data);
    void updateData() override;

private:
    QHash<int, int> indexes = { { 0, 0 }, { 201, 1 }, { 202, 2 }, { 203, 3 }, { 204, 4 }, { 205, 5 }, { 206, 6 }, { 210, 7 }, { 220, 8 }, { 221, 9 } };
};

class WeaponComboBox : public CustomEditor
{
    Q_OBJECT // NOLINT: Framework code, so can't fix this

public:
    explicit WeaponComboBox(int editorId, QWidget *buddyWidget = nullptr, CustomSpinBox *weaponAT = nullptr);

    QComboBox *editor;
    CustomSpinBox *wat = nullptr;

protected:
    void mouseReleaseEvent(QMouseEvent *event) override;

public slots: // NOLINT: False positive
    void updateSave(int data);
    void updateData() override;

private:
    QList<int> atValues = { 0, 3, 5, 7, 2, 10, 12, 15, 99 };
    QHash<int, int> indexes = { { 3, 0 }, { 13, 1 }, { 14, 2 }, { 25, 3 }, { 45, 4 }, { 47, 5 }, { 49, 6 }, { 51, 7 }, { 52, 8 } };
};

class ArmorComboBox : public CustomEditor
{
    Q_OBJECT // NOLINT: Framework code, so can't fix this

public:
    explicit ArmorComboBox(int editorId, QWidget *buddyWidget = nullptr, CustomSpinBox *armorDF = nullptr);

    QComboBox *editor;
    CustomSpinBox *adf = nullptr;

protected:
    void mouseReleaseEvent(QMouseEvent *event) override;

public slots: // NOLINT: False positive
    void updateSave(int data);
    void updateData() override;

private:
    QList<int> dfValues = { 0, 3, 7, 10, 5, 11, 12, 15, 99, 20 };
    QHash<int, int> indexes = { { 4, 0 }, { 12, 1 }, { 15, 2 }, { 24, 3 }, { 44, 4 }, { 46, 5 }, { 48, 6 }, { 50, 7 }, { 53, 8 }, { 64, 9 } };
};

class RoomComboBox : public CustomEditor
{
    Q_OBJECT // NOLINT: Framework code, so can't fix this

public:
    explicit RoomComboBox(int editorId, QWidget *buddyWidget = nullptr);

    QComboBox *editor;

protected:
    void mouseReleaseEvent(QMouseEvent *event) override;

public slots: // NOLINT: False positive
    void updateSave(int data);
    void updateData() override;

private:
    QHash<int, int> indexes = { { 6, 0 }, { 12, 1 }, { 18, 2 }, { 31, 3 }, { 46, 4 }, { 56, 5 }, { 61, 6 }, { 68, 7 }, { 83, 8 }, { 86, 9 }, { 94, 10 }, { 110, 11 }, { 114, 12 }, { 116, 13 }, { 128, 14 }, { 134, 15 }, { 139, 16 }, { 145, 17 }, { 155, 18 }, { 164, 19 }, { 176, 20 }, { 183, 21 }, { 196, 22 }, { 210, 23 }, { 216, 24 }, { 219, 25 }, { 231, 26 }, { 232, 27 }, { 235, 28 }, { 236, 29 }, { 246, 30 }, { 251, 31 }, { 0, 32 }, { 1, 33 }, { 2, 34 }, { 3, 35 }, { 4, 36 }, { 5, 37 }, { 7, 38 }, { 8, 39 }, { 9, 40 }, { 10, 41 }, { 11, 42 }, { 13, 43 }, { 14, 44 }, { 15, 45 }, { 16, 46 }, { 17, 47 }, { 19, 48 }, { 20, 49 }, { 21, 50 }, { 22, 51 }, { 23, 52 }, { 24, 53 }, { 25, 54 }, { 26, 55 }, { 27, 56 }, { 28, 57 }, { 29, 58 }, { 30, 59 }, { 32, 60 }, { 33, 61 }, { 34, 62 }, { 35, 63 }, { 36, 64 }, { 37, 65 }, { 38, 66 }, { 39, 67 }, { 40, 68 }, { 41, 69 }, { 42, 70 }, { 43, 71 }, { 44, 72 }, { 45, 73 }, { 47, 74 }, { 48, 75 }, { 49, 76 }, { 50, 77 }, { 51, 78 }, { 52, 79 }, { 53, 80 }, { 54, 81 }, { 55, 82 }, { 57, 83 }, { 58, 84 }, { 59, 85 }, { 60, 86 }, { 62, 87 }, { 63, 88 }, { 64, 89 }, { 65, 90 }, { 66, 91 }, { 67, 92 }, { 69, 93 }, { 70, 94 }, { 71, 95 }, { 72, 96 }, { 73, 97 }, { 74, 98 }, { 75, 99 }, { 76, 100 }, { 77, 101 }, { 78, 102 }, { 79, 103 }, { 80, 104 }, { 81, 105 }, { 82, 106 }, { 84, 107 }, { 85, 108 }, { 87, 109 }, { 88, 110 }, { 89, 111 }, { 90, 112 }, { 91, 113 }, { 92, 114 }, { 93, 115 }, { 95, 116 }, { 96, 117 }, { 97, 118 }, { 98, 119 }, { 99, 120 }, { 100, 121 }, { 101, 122 }, { 102, 123 }, { 103, 124 }, { 104, 125 }, { 105, 126 }, { 106, 127 }, { 107, 128 }, { 108, 129 }, { 109, 130 }, { 111, 131 }, { 112, 132 }, { 113, 133 }, { 115, 134 }, { 117, 135 }, { 118, 136 }, { 119, 137 }, { 120, 138 }, { 121, 139 }, { 122, 140 }, { 123, 141 }, { 124, 142 }, { 125, 143 }, { 126, 144 }, { 127, 145 }, { 129, 146 }, { 130, 147 }, { 131, 148 }, { 132, 149 }, { 133, 150 }, { 135, 151 }, { 136, 152 }, { 137, 153 }, { 138, 154 }, { 140, 155 }, { 141, 156 }, { 142, 157 }, { 143, 158 }, { 144, 159 }, { 146, 160 }, { 147, 161 }, { 148, 162 }, { 149, 163 }, { 150, 164 }, { 151, 165 }, { 152, 166 }, { 153, 167 }, { 154, 168 }, { 156, 169 }, { 157, 170 }, { 158, 171 }, { 159, 172 }, { 160, 173 }, { 161, 174 }, { 162, 175 }, { 163, 176 }, { 165, 177 }, { 166, 178 }, { 167, 179 }, { 168, 180 }, { 169, 181 }, { 170, 182 }, { 171, 183 }, { 172, 184 }, { 173, 185 }, { 174, 186 }, { 175, 187 }, { 177, 188 }, { 178, 189 }, { 179, 190 }, { 180, 191 }, { 181, 192 }, { 182, 193 }, { 184, 194 }, { 185, 195 }, { 186, 196 }, { 187, 197 }, { 188, 198 }, { 189, 199 }, { 190, 200 }, { 191, 201 }, { 192, 202 }, { 193, 203 }, { 194, 204 }, { 195, 205 }, { 197, 206 }, { 198, 207 }, { 199, 208 }, { 200, 209 }, { 201, 210 }, { 202, 211 }, { 203, 212 }, { 204, 213 }, { 205, 214 }, { 206, 215 }, { 207, 216 }, { 208, 217 }, { 209, 218 }, { 211, 219 }, { 212, 220 }, { 213, 221 }, { 214, 222 }, { 215, 223 }, { 217, 224 }, { 218, 225 }, { 220, 226 }, { 221, 227 }, { 222, 228 }, { 223, 229 }, { 224, 230 }, { 225, 231 }, { 226, 232 }, { 227, 233 }, { 228, 234 }, { 229, 235 }, { 230, 236 }, { 233, 237 }, { 234, 238 }, { 237, 239 }, { 238, 240 }, { 239, 241 }, { 240, 242 }, { 241, 243 }, { 242, 244 }, { 243, 245 }, { 244, 246 }, { 245, 247 }, { 247, 248 }, { 248, 249 }, { 249, 250 }, { 250, 251 }, { 252, 252 }, { 253, 253 }, { 254, 254 }, { 255, 255 }, { 256, 256 }, { 257, 257 }, { 258, 258 }, { 259, 259 }, { 260, 260 }, { 261, 261 }, { 262, 262 }, { 263, 263 }, { 264, 264 }, { 265, 265 }, { 266, 266 }, { 267, 267 }, { 268, 268 }, { 269, 269 }, { 270, 270 }, { 271, 271 }, { 272, 272 }, { 273, 273 }, { 274, 274 }, { 275, 275 }, { 276, 276 }, { 277, 277 }, { 278, 278 }, { 279, 279 }, { 280, 280 }, { 281, 281 }, { 282, 282 }, { 283, 283 }, { 284, 284 }, { 285, 285 }, { 286, 286 }, { 287, 287 }, { 288, 288 }, { 289, 289 }, { 290, 290 }, { 291, 291 }, { 292, 292 }, { 293, 293 }, { 294, 294 }, { 295, 295 }, { 296, 296 }, { 297, 297 }, { 298, 298 }, { 299, 299 }, { 300, 300 }, { 301, 301 }, { 302, 302 }, { 303, 303 }, { 304, 304 }, { 305, 305 }, { 306, 306 }, { 307, 307 }, { 308, 308 }, { 309, 309 }, { 310, 310 }, { 311, 311 }, { 312, 312 }, { 313, 313 }, { 314, 314 }, { 315, 315 }, { 316, 316 }, { 317, 317 }, { 318, 318 }, { 319, 319 }, { 320, 320 }, { 321, 321 }, { 322, 322 }, { 323, 323 }, { 324, 324 }, { 325, 325 }, { 326, 326 }, { 327, 327 }, { 328, 328 }, { 329, 329 }, { 330, 330 }, { 331, 331 }, { 332, 332 }, { 333, 333 }, { 334, 334 } };
};

class TimeEdit : public CustomEditor
{
    Q_OBJECT // NOLINT: Framework code, so can't fix this

public:
    explicit TimeEdit(int editorId, QWidget *buddyWidget = nullptr);

    QDoubleSpinBox *editor;

public slots: // NOLINT: False positive
    void updateSave();
    void updateData() override;
};

class PlotEdit : public CustomEditor
{
    Q_OBJECT // NOLINT: Framework code, so can't fix this

public:
    explicit PlotEdit(int editorId, QWidget *buddyWidget = nullptr);

    QComboBox *editor;

protected:
    void mouseReleaseEvent(QMouseEvent *event) override;

public slots: // NOLINT: False positive
    void updateSave(int data);
    void updateData() override;

private:
    const QHash<double, int> indexes = { { 0, 0 }, { 1, 1 }, { 2, 2 }, { 3, 3 }, { 4, 4 }, { 4.5, 5 }, { 5, 6 }, { 5.5, 7 }, { 6, 8 }, { 7, 9 }, { 7.5, 10 }, { 8, 11 }, { 8.5, 12 }, { 9, 13 }, { 9.2, 14 }, { 9.4, 15 }, { 9.6, 16 }, { 9.8, 17 }, { 10.3, 18 }, { 10.35, 19 }, { 10.4, 20 }, { 11, 21 }, { 12, 22 }, { 13, 23 }, { 14, 24 }, { 15, 25 }, { 16, 26 }, { 17, 27 }, { 18, 28 }, { 19, 29 }, { 19.1, 30 }, { 19.2, 31 }, { 19.3, 32 }, { 19.4, 33 }, { 19.9, 34 }, { 20, 35 }, { 21, 36 }, { 22, 37 }, { 23, 38 }, { 24, 39 }, { 25, 40 }, { 28, 41 }, { 30, 42 }, { 36, 43 }, { 37, 44 }, { 40, 45 }, { 41, 46 }, { 42, 47 }, { 43, 48 }, { 47, 49 }, { 49, 50 }, { 50, 51 }, { 51, 52 }, { 53, 53 }, { 54, 54 }, { 56, 55 }, { 57, 56 }, { 58, 57 }, { 60, 58 }, { 61, 59 }, { 63, 60 }, { 65, 61 }, { 67, 62 }, { 100, 63 }, { 101, 64 }, { 104, 65 }, { 106, 66 }, { 107, 67 }, { 108, 68 }, { 109, 69 }, { 110, 70 }, { 111, 71 }, { 112, 72 }, { 113, 73 }, { 115, 74 }, { 116, 75 }, { 117, 76 }, { 118, 77 }, { 119, 78 }, { 120, 79 }, { 121, 80 }, { 122, 81 }, { 126, 82 }, { 127, 83 }, { 130, 84 }, { 131, 85 }, { 132, 86 }, { 133, 87 }, { 133.5, 88 }, { 134, 89 }, { 135, 90 }, { 137, 91 }, { 139, 92 }, { 140, 93 }, { 143, 94 }, { 146, 95 }, { 160, 96 }, { 161, 97 }, { 162, 98 }, { 163, 99 }, { 164, 100 }, { 165, 101 }, { 167, 102 }, { 168, 103 }, { 176, 104 }, { 177, 105 }, { 179, 106 }, { 180, 107 }, { 181, 108 }, { 182, 109 }, { 183, 110 }, { 184, 111 }, { 185, 112 }, { 193, 113 }, { 199, 114 }, { 201, 115 }, { 206, 116 }, { 207, 117 }, { 208, 118 }, { 999, 119 } };
};

#endif // TOOLS_H
