curl -X POST \
  'http://ec2-18-222-19-9.us-east-2.compute.amazonaws.com:8011/api/v1/tasks' \
  -H 'Cache-Control: no-cache' \
  -H 'Content-Type: application/json' \
  -H 'Postman-Token: 6499dae4-db3e-4940-bd99-7708db44d9d6' \
  -d '[{"taskType":"inspect","orderExternal":"33541","station":"097385ce-182b-498c-85be-bc31b4b6012a","rack":"f2cc2661-24ec-45a7-9269-0833c7235923","cell":"dc8c3453-c3a1-4ec2-9d60-5f7d4d908a8e"}]'
