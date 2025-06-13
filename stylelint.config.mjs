export default {
    extends: "stylelint-config-recommended",
    plugins: [
        "stylelint-order",
    ],
    rules: {
        "order/properties-alphabetical-order": true,
        "no-descending-specificity": null,
    },
};
